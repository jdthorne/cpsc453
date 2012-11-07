
// System
#include <cmath>

// Project
#include <Vector.h>
#include <Ray.h>
#include <Raytracer.h>

Raytracer::Raytracer()
   : imageWidth_(1280 / 2)
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
   Vector startPoint = Vector(0, 0, 100);

   Vector throughVirtualScreen = Vector(x - (imageWidth_ / 2),
                                        y - (imageHeight_ / 2),
                                        50);

   Ray ray = Ray::fromTo(startPoint, throughVirtualScreen);

   return trace(ray);   
}

Color Raytracer::trace(Ray ray)
{
   double bestDistance = 9999999;
   PossibleRayIntersection bestIntersection = PossibleRayIntersection::noIntersection();

   foreach (SceneObject* object, scene_.objects())
   {
      PossibleRayIntersection possibleIntersection = object->findIntersectionWith(ray);

      if (possibleIntersection.exists())
      {
         double distance = possibleIntersection.intersection().distance();
         if (distance < bestDistance)
         {
            bestDistance = distance;
            bestIntersection = possibleIntersection;
         }
      }
   }

   if (!bestIntersection.exists())
   {
      return Color(0, 0, 0);
   }

   RayIntersection intersection = bestIntersection.intersection();
   double phongLongDong = fabs(ray.direction().dot(intersection.surfaceNormal()));

   return Color(phongLongDong, phongLongDong, 0);
}

