
// System
#include <cmath>

// Project
#include <Vector.h>
#include <Ray.h>
#include <Raytracer.h>

Raytracer::Raytracer()
   : cameraPosition_(0, 0, 100)
   , imageWidth_(1280 / 2)
   , imageHeight_(720 / 2)
{
}

Raytracer::~Raytracer()
{
}

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

Color Raytracer::traceInitialRay(int x, int y)
{
   Vector startPoint = cameraPosition_;

   Vector throughVirtualScreen = Vector(x - (imageWidth_ / 2),
                                        y - (imageHeight_ / 2),
                                        -1000);

   Ray ray = Ray::fromTo(startPoint, throughVirtualScreen);

   return trace(ray);   
}

Color Raytracer::trace(Ray ray)
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
   Color reflectedLight = totalReflectedLightAt(intersection);

   return directLight + reflectedLight;
}

Color Raytracer::totalDirectLightAt(RayIntersection intersection)
{
   Color result = Color(0, 0, 0);

   foreach (SceneLight* light, scene_.lights())
   {
      double distanceToLight = intersection.point().distanceTo(light->position());
      
      Ray rayToLight = Ray::fromTo(intersection.point(), light->position());
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

Color Raytracer::totalReflectedLightAt(RayIntersection intersection)
{
   return Color(0, 0, 0);
}

Color Raytracer::diffuseLightAt(RayIntersection intersection, const SceneLight& light)
{
   Vector intersectionToLight = (light.position() - intersection.point()).normalized();

   double intensity = intersectionToLight.dot(intersection.surfaceNormal());
   return Color(1, 0, 0) * intensity;
}

Color Raytracer::specularLightAt(RayIntersection intersection, const SceneLight& light)
{
   Vector intersectionToLight = (light.position() - intersection.point()).normalized();
   Vector intersectionToViewport = (cameraPosition_ - intersection.point()).normalized();

   Vector halfVector = (intersectionToLight + intersectionToViewport).normalized();

   double intensity = pow(halfVector.dot(intersection.surfaceNormal()), 6);

   return Color(0, 1, 0) * (intensity * 0.5);
}

