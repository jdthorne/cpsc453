
// System
#include <cmath>

// Project
#include <Vector.h>
#include <Ray.h>
#include <Raytracer.h>

Raytracer::Raytracer()
   : cameraPosition_(0, 0, 25)
   , imageWidth_(1280 / 2)
   , imageHeight_(720 / 2)
{
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
QImage Raytracer::run()
{
   QImage result = QImage(QSize(imageWidth_, imageHeight_), QImage::Format_RGB32);

   for (int x = 0; x < result.width(); x++)
   {
      for (int y = 0; y < result.height(); y++)
      {
         Color pixelColor = traceInitialRay(x, y);
         result.setPixel(x, y, pixelColor.toQtRgb());
      }
   }

   return result;
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
Color Raytracer::trace(Ray ray, int depth)
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

   // The resulting color consists of:
   Color directLight = totalDirectLightAt(intersection);
   Color reflectedLight = totalReflectedLightAt(intersection, depth);

   return directLight + reflectedLight;
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
   Color result = Color(0, 0, 0);

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

Color Raytracer::diffuseLightAt(RayIntersection intersection, const Light& light)
{
   Vector intersectionToLight = (light.position() - intersection.point()).normalized();

   Material material = intersection.material();

   double positionalIntensity = intersectionToLight.dot(intersection.surfaceNormal());
   return material.diffuseColor * material.diffuseIntensity * positionalIntensity;
}

Color Raytracer::specularLightAt(RayIntersection intersection, const Light& light)
{
   Vector lightVector = (intersection.point() - light.position()).normalized();
   Vector lightReflectedVector = lightVector.reflected(intersection.surfaceNormal());

   Vector viewportVector = (cameraPosition_ - intersection.point()).normalized();

   Material material = intersection.material();

   double rDotV = qMax(0.0, lightReflectedVector.dot(viewportVector));
   double positionalIntensity = pow(rDotV, material.specularSpread);

   return material.specularColor * positionalIntensity * material.specularIntensity;
}

/**
 ******************************************************************************
 *
 *                   Reflections
 *
 ******************************************************************************
 */
Color Raytracer::totalReflectedLightAt(RayIntersection intersection, int depth)
{
   if (depth > 3 || intersection.material().reflectance == 0.0)
   {
      return Color(0, 0, 0);
   }

   return trace(intersection.reflectedRay(), depth + 1) * intersection.material().reflectance;
}
