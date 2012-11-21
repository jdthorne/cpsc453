
// System
#include <cmath>

// Project
#include <Cylinder.h>

Cylinder::Cylinder(Vector position, double height, double radius, Material material)
   : SceneObject(position, material)
   , height_(height)
   , radius_(radius)
   , axis_(0, 1, 0)
{
}

Cylinder::~Cylinder()
{
}

/**
 ******************************************************************************
 *
 *                   Load a cylinder from a file definition
 *
 ******************************************************************************
 */
Cylinder* Cylinder::newFromFile(PropertyList properties)
{
   return new Cylinder(properties.vector("Position"),
                       properties.scalar("Height"),
                       properties.scalar("Radius"),
                       properties.material("Material"));
}

/**
 ******************************************************************************
 *
 *                   Find a ray intersection with the cylinder
 *
 ******************************************************************************
 */
PossibleRayIntersection Cylinder::findIntersectionWith(Ray ray)
{
   Vector start = ray.start();
   Vector direction = ray.direction();

   // Calculate a, b, c values for quadratic equation
   double a = pow(direction.x(), 2) + pow(direction.z(), 2);
   double b = (2 * start.x() * direction.x()) + (2 * start.z() * direction.z());
   double c = pow(start.x(), 2) + pow(start.z(), 2) - radius_;

   // Calculate value under sqrt
   double valueUnderSquareRoot = pow(b, 2) - (4 * a * c);

   // Return no intersection (if there is no intersection)
   if (valueUnderSquareRoot < 0)
   {
      return PossibleRayIntersection::noIntersection();   
   }

   // Calculate possible distances
   double distance1 = (-b + sqrt(valueUnderSquareRoot)) / (2 * a);
   double distance2 = (-b - sqrt(valueUnderSquareRoot)) / (2 * a);

   // Get best distance
   double distance = qMin(distance1, distance2);

   if (distance < 0)
   {
      return PossibleRayIntersection::noIntersection();
   }

   // Calculate intersection point, ensure it's on the cylinder
   Vector intersectionPoint = ray.start() + (ray.direction() * distance);
   double heightUpCylinder = fabs( (intersectionPoint - origin_).dot(axis_) );

   if (heightUpCylinder > height_ / 2)
   {
      return PossibleRayIntersection::noIntersection();
   }

   // Calculate surface normal
   Vector corePoint = Vector(origin_.x(), intersectionPoint.y(), origin_.z());
   Vector normal = (intersectionPoint - corePoint).normalized();

   // Return intersection
   return RayIntersection(ray, distance, normal, material_);
}
