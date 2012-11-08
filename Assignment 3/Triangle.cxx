
// System

// Project
#include <Triangle.h>

Triangle::Triangle(Vector position, Vector pointTwo, Vector pointThree, Material material)
   : SceneObject(position, material)
   , pointTwo_(pointTwo)
   , pointThree_(pointThree)
   , normal_( (pointTwo - position).cross(pointThree - position) )
{
}

Triangle::~Triangle()
{
}

PossibleRayIntersection Triangle::findIntersectionWith(Ray ray)
{
   double denominator = ray.direction().dot(normal_);

   if (denominator == 0)
   {
      return PossibleRayIntersection::noIntersection();
   }

   double numerator = (center_ - ray.start()).dot(normal_);

   double distance = numerator / denominator;

   if (distance < 0)
   {
      return PossibleRayIntersection::noIntersection();
   }

   return RayIntersection(ray, distance, normal_, material_);
}

