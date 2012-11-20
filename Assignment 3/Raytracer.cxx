
// System
#include <cmath>

// Qt
#include <QElapsedTimer>

// Project
#include <Vector.h>
#include <Ray.h>
#include <Raytracer.h>

Raytracer::Raytracer(Scene& scene)
   : scene_(scene)
   , cameraPosition_(0, 0, 25)
   , imageWidth_(1280 / 2)
   , imageHeight_(720 / 2)
   , y_(0)
{
   result_ = QImage(QSize(imageWidth_, imageHeight_), QImage::Format_RGB32);
}

Raytracer::~Raytracer()
{
}

/**
 ******************************************************************************
 *
 *                   Main Entry Point
 *
 ******************************************************************************
 */
bool Raytracer::running()
{
   return (y_ < imageHeight_);
}

QImage Raytracer::run()
{
   QElapsedTimer timer;
   timer.start();

   while (running() && timer.elapsed() < 100)
   {
      for (int x = 0; x < result_.width(); x++)
      {
         Color pixelColor = traceInitialRay(x, y_);
         result_.setPixel(x, y_, pixelColor.toQtRgb());
      }

      y_++;
   }

   return result_;
}

/**
 ******************************************************************************
 *
 *                   Raytracing Bootstrap Function
 *
 ******************************************************************************
 */
Color Raytracer::traceInitialRay(int x, int y)
{
   Vector startPoint = cameraPosition_;

   Vector throughVirtualScreen = Vector(x - (imageWidth_ / 2),
                                        y - (imageHeight_ / 2),
                                        -350);

   Ray ray = Ray::fromPointToPoint(startPoint, throughVirtualScreen);

   return trace(ray);
}

/**
 ******************************************************************************
 *
 *                   Core Raytracing Function
 *
 ******************************************************************************
 */
Color Raytracer::trace(Ray ray, RaytracerStatus status)
{
   // See if the ray intersects with an object
   PossibleRayIntersection possibleIntersection = scene_.findFirstIntersection(ray);

   // If not, return sky color
   if (!possibleIntersection.exists())
   {
      return Color(0, 0, 0);
   }

   // Otherwise, grab the intersection
   RayIntersection intersection = possibleIntersection.intersection();

   // If we're leaving an object, just calculate the refraction
   if (status.rayIsInsideObject())
   {
      return totalRefractedLightAt(intersection, status);
   }

   // Otherwise, calculate the surface color
   Color surfaceColor = totalDirectLightAt(intersection) 
                        + totalReflectedLightAt(intersection, status)
                        + totalRefractedLightAt(intersection, status);

   return surfaceColor;
}

/**
 ******************************************************************************
 *
 *                   Direct Lighting (e.g. phong)
 *
 ******************************************************************************
 */
Color Raytracer::totalDirectLightAt(RayIntersection intersection)
{
   Color result = ambientLightAt(intersection);

   foreach (Light* light, scene_.lights())
   {
      double distanceToLight = intersection.point().distanceTo(light->position());
      
      Ray rayToLight = Ray::fromPointToPoint(intersection.point(), light->position());
      PossibleRayIntersection objectInTheWay = scene_.findFirstIntersection(rayToLight);

      bool shadow = (objectInTheWay.exists() && objectInTheWay.intersection().distance() < distanceToLight);
      if (!shadow)
      {
         result += diffuseLightAt(intersection, *light);
         result += specularLightAt(intersection, *light);
      }
   }

   return result;
}

Color Raytracer::ambientLightAt(RayIntersection intersection)
{
   return scene_.ambientLight() * intersection.material().diffuseColor;
}

Color Raytracer::diffuseLightAt(RayIntersection intersection, const Light& light)
{
   Vector intersectionToLight = (light.position() - intersection.point()).normalized();

   Material material = intersection.material();

   double positionalIntensity = fabs(intersectionToLight.dot(intersection.surfaceNormal()));
   return (material.diffuseColor * light.color()) * material.diffuseIntensity * positionalIntensity;
}

Color Raytracer::specularLightAt(RayIntersection intersection, const Light& light)
{
   Vector lightVector = (intersection.point() - light.position()).normalized();
   Vector lightReflectedVector = lightVector.reflected(intersection.surfaceNormal());

   Vector viewportVector = (cameraPosition_ - intersection.point()).normalized();

   Material material = intersection.material();

   double rDotV = qMax(0.0, lightReflectedVector.dot(viewportVector));
   double positionalIntensity = pow(rDotV, material.specularSpread);

   return (material.specularColor * light.color()) * positionalIntensity * material.specularIntensity;
}

/**
 ******************************************************************************
 *
 *                   Reflections
 *
 ******************************************************************************
 */
Color Raytracer::totalReflectedLightAt(RayIntersection intersection, RaytracerStatus status)
{
   if (status.outOfDepth() || intersection.material().reflectance == 0.0)
   {
      return Color(0, 0, 0);
   }

   Color reflectedColor = trace(intersection.reflectedRay(), status.nextRecursion());
   return reflectedColor * intersection.material().reflectance;
}

/**
 ******************************************************************************
 *
 *                   Refractions
 *
 ******************************************************************************
 */
Color Raytracer::totalRefractedLightAt(RayIntersection intersection, RaytracerStatus status)
{
   if (status.outOfDepth() || intersection.material().transparency == 0.0)
   {
      return Color(0, 0, 0);
   }

   double refraction = intersection.material().refraction;
   Vector incoming = intersection.incomingRay().direction();
   Vector normal = intersection.surfaceNormal();

   if (status.rayIsInsideObject())
   {
     refraction = 1.0 / refraction;
     normal = normal * -1.0;
   }

   double cosi = (incoming * -1).dot(normal);
   double cost2 = 1.0 - pow(refraction, 2) * (1 - pow(cosi, 2));

   if (cost2 <= 0)
   {
      return Color(0, 0, 0);
   }  

   Vector refractedRay = (incoming * refraction) + (normal * (refraction * cosi - sqrt(fabs(cost2))));

   Ray continuingRay = Ray::fromStartAndDirection(intersection.point(), 
                                                  refractedRay);


   Color refractedColor = trace(continuingRay, status.nextRecursionDueToRefraction());
   return refractedColor * intersection.material().transparency;
}
