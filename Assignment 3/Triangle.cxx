
// System

// Project
#include <Triangle.h>

Triangle::Triangle(Vector p1, Vector p2, Vector p3, Material material)
   : SceneObject(p1, material)
   , p1_(p1)
   , p2_(p2)
   , p3_(p3)
   , normal_( (p2 - p1).cross(p3 - p1).normalized() )
{
}

Triangle::~Triangle()
{
}

Triangle* Triangle::newFromFile(PropertyList properties)
{
   return new Triangle(properties.vector("P1"),
                       properties.vector("P2"),
                       properties.vector("P3"),
                       properties.material("Material"));
}

PossibleRayIntersection Triangle::findIntersectionWith(Ray ray)
{
   double denominator = ray.direction().dot(normal_);

   if (denominator == 0)
   {
      return PossibleRayIntersection::noIntersection();
   }

   double numerator = (origin_ - ray.start()).dot(normal_);
   double distance = numerator / denominator;

   if (distance < 0)
   {
      return PossibleRayIntersection::noIntersection();
   }

   Vector p = ray.start() + (ray.direction() * distance);

   double x = ( (p - p1_).normalized()
              + (p - p2_).normalized()
              + (p - p3_).normalized() ).magnitude();

   if (x > 1)
   {
      return PossibleRayIntersection::noIntersection();
   }

   return RayIntersection(ray, distance, normal_, material_);
}
