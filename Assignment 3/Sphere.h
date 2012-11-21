#ifndef SPHERE_H
#define SPHERE_H

// System

// Project
#include <SceneObject.h>
#include <PropertyList.h>

/**
 ******************************************************************************
 *
 *                   Sphere
 *
 * Represents a raytracable sphere within a scene
 *
 ******************************************************************************
 */
class Sphere : public SceneObject
{

public:
   Sphere(Vector postion, double radius, Material material);
   virtual ~Sphere();

   static Sphere* newFromFile(PropertyList properties);

public:
   virtual PossibleRayIntersection findIntersectionWith(Ray ray);

protected: // helpers
   PossibleRayIntersection intersectionGivenDistance(Ray ray, double distance);
   double smallestPositiveValue(double a, double b);

private:
   double radius_;
};

#endif
