
// System
#include <cmath>

// Qt
#include <QTime>

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

   // Initialize the image to black
   for (int x = 0; x < imageWidth_; x++)
   {
      for (int y = 0; y < imageHeight_; y++)
      {
         result_.setPixel(x, y, 0);
      }
   }
}

Raytracer::~Raytracer()
{
}

/**
 ******************************************************************************
 *
 *                   Determine if the raytracer is still running
 *
 ******************************************************************************
 */
bool Raytracer::running()
{
   return (y_ < imageHeight_);
}

/**
 ******************************************************************************
 *
 *                   Main run() function
 *
 ******************************************************************************
 */
QImage Raytracer::run()
{
   // Save when we started
   QTime start = QTime::currentTime();

   // Continue while we're running, and haven't spent too long
   while (running() && start.msecsTo(QTime::currentTime()) < 100)
   {
      // Render a full row
      for (int x = 0; x < result_.width(); x++)
      {
         // Trace a ray, save it to the image
         Color pixelColor = traceInitialRay(x, y_);
         result_.setPixel(x, y_, pixelColor.toQtRgb());
      }

      // Move to the next row
      y_++;
   }

   qDebug("[Raytracer] Rendering is %.2f percent complete...", 100.0 * (double)y_ / imageHeight_);

   // Return the image in progress
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
   // Find the start point
   Vector startPoint = cameraPosition_;

   // Find the virtual screen point
   Vector throughVirtualScreen = Vector(x - (imageWidth_ / 2),
                                        y - (imageHeight_ / 2),
                                        scene_.planeDepth());

   // Build the ray connecting the points
   Ray ray = Ray::fromPointToPoint(startPoint, throughVirtualScreen);

   // Trace the ray
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
   // Start with ambient light
   Color result = ambientLightAt(intersection);

   // Loop through lights
   foreach (Light* light, scene_.lights())
   {
      // Find the distance
      double distanceToLight = intersection.point().distanceTo(light->position());
         
      // See if there is an object in the way
      Ray rayToLight = Ray::fromPointToPoint(intersection.point(), light->position());
      PossibleRayIntersection objectInTheWay = scene_.findFirstIntersection(rayToLight);

      // If no shadow, calculate diffuse and specular lighting
      bool shadow = (objectInTheWay.exists() && objectInTheWay.intersection().distance() < distanceToLight);
      if (!shadow)
      {
         result += diffuseLightAt(intersection, *light);
         result += specularLightAt(intersection, *light);
      }
   }

   return result;
}

//
// Ambient light function - just ambient light * difuse color
//
Color Raytracer::ambientLightAt(RayIntersection intersection)
{
   return scene_.ambientLight() * intersection.material().diffuseColor;
}

//
// Diffuse light function - phong lighting
//
Color Raytracer::diffuseLightAt(RayIntersection intersection, const Light& light)
{
   // Determine vector from point to light
   Vector intersectionToLight = (light.position() - intersection.point()).normalized();

   // Grab surface material
   Material material = intersection.material();

   // Determine the phong intensity
   double positionalIntensity = fabs(intersectionToLight.dot(intersection.surfaceNormal()));

   // Return the colors mixed, multiplied by the intensity
   return (material.diffuseColor * light.color()) * material.diffuseIntensity * positionalIntensity;
}

//
// Specular light function - phong lighting
//
Color Raytracer::specularLightAt(RayIntersection intersection, const Light& light)
{
   // Find vector to light, reflected vector
   Vector lightVector = (intersection.point() - light.position()).normalized();
   Vector lightReflectedVector = lightVector.reflected(intersection.surfaceNormal());

   // Find viewport vector
   Vector viewportVector = (cameraPosition_ - intersection.point()).normalized();

   // Grab material
   Material material = intersection.material();

   // Calcualte phong values
   double rDotV = qMax(0.0, lightReflectedVector.dot(viewportVector));
   double positionalIntensity = pow(rDotV, material.specularSpread);

   // Return mixed color
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
   // Cancel raytracing if we're out of depth (or not reflecting)
   if (status.outOfDepth() || intersection.material().reflectance == 0.0)
   {
      return Color(0, 0, 0);
   }

   // Trace the reflected ray
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
   // Cancel raytracing if we're out of depth (or not transparent)
   if (status.outOfDepth() || intersection.material().transparency == 0.0)
   {
      return Color(0, 0, 0);
   }

   // Grab vectors
   double refraction = intersection.material().refraction;
   Vector incoming = intersection.incomingRay().direction();
   Vector normal = intersection.surfaceNormal();

   // Invert snell values if we're inside the object
   if (status.rayIsInsideObject())
   {
     refraction = 1.0 / refraction;
     normal = normal * -1.0;
   }

   // Calculate snell values
   double cosi = (incoming * -1).dot(normal);
   double cost2 = 1.0 - pow(refraction, 2) * (1 - pow(cosi, 2));

   // Return black if we hit total internal reflection
   if (cost2 <= 0)
   {
      return Color(0, 0, 0);
   }  

   // Find the refracted ray
   Vector refractedRay = (incoming * refraction) + (normal * (refraction * cosi - sqrt(fabs(cost2))));
   Ray continuingRay = Ray::fromStartAndDirection(intersection.point(), 
                                                  refractedRay);


   // Trace it
   Color refractedColor = trace(continuingRay, status.nextRecursionDueToRefraction());
   return refractedColor * intersection.material().transparency;
}
