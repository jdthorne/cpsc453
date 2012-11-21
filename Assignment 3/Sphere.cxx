
// System
#include <cmath>

// Project
#include <Sphere.h>

Sphere::Sphere(Vector position, double radius, Material material)
   : SceneObject(position, material)
   , radius_(radius)
{
}

/**
 ******************************************************************************
 *
 *                   Return a sphere from a propertylist
 *
 ******************************************************************************
 */
Sphere* Sphere::newFromFile(PropertyList properties)
{
   return new Sphere(properties.vector("Position"), 
                     properties.scalar("Radius"),
                     properties.material("Material"));
}

Sphere::~Sphere()
{
}

/**
 ******************************************************************************
 *
 *                   Find an intersection with a ray
 *
 ******************************************************************************
 */
PossibleRayIntersection Sphere::findIntersectionWith(Ray ray)
{
   // Grab vectors
   Vector line = ray.direction();
   Vector relativeCenter = (origin_ - ray.start());

   // Do math
   double lineDotCenterSquared = pow(line.dot(relativeCenter), 2);
   double centerSquared = pow(relativeCenter.magnitude(), 2);
   double radiusSquared = pow(radius_, 2);

   double valueUnderSquareRoot =  (lineDotCenterSquared - centerSquared + radiusSquared);

   double lineDotCenter = line.dot(relativeCenter);

   // Case 1: No solutions exist; return no intersection
   if (valueUnderSquareRoot < 0)
   {
      return PossibleRayIntersection::noIntersection();
   }

   // Case 2: Exactly one solution exists; return the intersection
   else if (fabs(valueUnderSquareRoot) < 0.000001)
   {
      double distance = lineDotCenter;
      return intersectionGivenDistance(ray, distance);
   }

   // Case 3: Multiple solutions; return best intersection
   else
   {
      // Find both distances
      double squareRoot = sqrt(valueUnderSquareRoot);
      double distanceA = lineDotCenter + squareRoot;
      double distanceB = lineDotCenter - squareRoot;

      // Find best distance
      double distance = smallestPositiveValue(distanceA, distanceB);

      // Return intersection
      return intersectionGivenDistance(ray, distance);
   }
 }

/**
 ******************************************************************************
 *
 *                   Helper to build an intersection given a distance
 *
 ******************************************************************************
 */
PossibleRayIntersection Sphere::intersectionGivenDistance(Ray ray, double distance)
{
   // Distances must be >0
   if (distance < 0)
   {
      return PossibleRayIntersection::noIntersection();
   }

   // Calculate normal
   Vector intersectionPoint = ray.start() + (ray.direction() * distance);
   Vector relativeIntersectionPoint = intersectionPoint - origin_;

   Vector surfaceNormal = relativeIntersectionPoint.normalized();

   // Return intersection
   return RayIntersection(ray, distance, surfaceNormal, material_);
}

