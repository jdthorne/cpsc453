
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

   Ray ray = Ray::fromPointToPoint(startPoint, throughVirtualScreen);

   return trace(ray);   
}

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
   //Color reflectedLight = totalReflectedLightAt(intersection, depth);

   return directLight;// + reflectedLight;
}

Color Raytracer::totalDirectLightAt(RayIntersection intersection)
{
   Color result = Color(0, 0, 0);

   foreach (SceneLight* light, scene_.lights())
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

Color Raytracer::totalReflectedLightAt(RayIntersection intersection, int depth)
{
   if (depth > 6 || intersection.material().reflectance == 0.0)
   {
      return Color(0, 0, 0);
   }

   return trace(intersection.reflectedRay(), depth + 1) * intersection.material().reflectance;
}

Color Raytracer::diffuseLightAt(RayIntersection intersection, const SceneLight& light)
{
   Vector intersectionToLight = (light.position() - intersection.point()).normalized();

   double intensity = intersectionToLight.dot(intersection.surfaceNormal());
   return intersection.material().diffuseColor * intensity;
}

Color Raytracer::specularLightAt(RayIntersection intersection, const SceneLight& light)
{
   Vector intersectionToLight = (light.position() - intersection.point()).normalized();
   Vector intersectionToViewport = (cameraPosition_ - intersection.point()).normalized();

   Vector halfVector = (intersectionToLight + intersectionToViewport).normalized();

   Material material = intersection.material();

   double intensity = pow(halfVector.dot(intersection.surfaceNormal()), material.specularity);

   return material.specularColor * intensity;
}

