
// System
#include <cmath>

// Project
#include <Sphere.h>

Sphere::Sphere(Vector position, double radius, Material material)
   : SceneObject(position, material)
   , radius_(radius)
{
}

Sphere* Sphere::newFromFile(PropertyList properties)
{
   return new Sphere(properties.vector("Position"), 
                     properties.scalar("Radius"),
                     properties.material("Material"));
}

Sphere::~Sphere()
{
}

PossibleRayIntersection Sphere::findIntersectionWith(Ray ray)
{
   Vector line = ray.direction();
   Vector relativeCenter = (origin_ - ray.start());

   double lineDotCenterSquared = pow(line.dot(relativeCenter), 2);
   double centerSquared = pow(relativeCenter.magnitude(), 2);
   double radiusSquared = pow(radius_, 2);

   double valueUnderSquareRoot =  (lineDotCenterSquared - centerSquared + radiusSquared);

   double lineDotCenter = line.dot(relativeCenter);

   // Case 1: No solutions exist
   if (valueUnderSquareRoot < 0)
   {
      return PossibleRayIntersection::noIntersection();
   }

   // Case 2: Exactly one solution exists
   else if (fabs(valueUnderSquareRoot) < 0.000001)
   {
      double distance = lineDotCenter;
      return intersectionGivenDistance(ray, distance);
   }

   // Case 3: Multiple solutions
   else
   {
      double squareRoot = sqrt(valueUnderSquareRoot);
      double distanceA = lineDotCenter + squareRoot;
      double distanceB = lineDotCenter - squareRoot;

      double distance = smallestPositiveValue(distanceA, distanceB);

      return intersectionGivenDistance(ray, distance);
   }
 }

PossibleRayIntersection Sphere::intersectionGivenDistance(Ray ray, double distance)
{
   if (distance < 0)
   {
      return PossibleRayIntersection::noIntersection();
   }

   Vector intersectionPoint = ray.start() + (ray.direction() * distance);
   Vector relativeIntersectionPoint = intersectionPoint - origin_;

   Vector surfaceNormal = relativeIntersectionPoint.normalized();

   return RayIntersection(ray, distance, surfaceNormal, material_);
}

double Sphere::smallestPositiveValue(double a, double b)
{
   if (a < 0.0000001)
   {
      return b;
   }
   else if (b < 0.0000001)
   {
      return a;
   }
   else if (a < b)
   {
      return a;
   }
   return b;
}

