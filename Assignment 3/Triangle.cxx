
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

/**
 ******************************************************************************
 *
 *                   Create a triangle from a file
 *
 ******************************************************************************
 */
Triangle* Triangle::newFromFile(PropertyList properties)
{
   return new Triangle(properties.vector("P1"),
                       properties.vector("P2"),
                       properties.vector("P3"),
                       properties.material("Material"));
}

/**
 ******************************************************************************
 *
 *                   Calculate triangle intersection
 *
 ******************************************************************************
 */
PossibleRayIntersection Triangle::findIntersectionWith(Ray ray)
{
   // Determine if ray intersects with the triangle's plane
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

   // If so, find intersection point
   Vector p = ray.start() + (ray.direction() * distance);

   // Calculate the x-value for angle intersection method
   double x = ( (p - p1_).normalized()
              + (p - p2_).normalized()
              + (p - p3_).normalized() ).magnitude();

   // Determine if point falls within triangle
   if (x > 1)
   {
      return PossibleRayIntersection::noIntersection();
   }

   // Return the intersection
   return RayIntersection(ray, distance, normal_, material_);
}
