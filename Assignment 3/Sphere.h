#ifndef SPHERE_H
#define SPHERE_H

// System

// Project
#include <SceneObject.h>

/**
 ******************************************************************************
 *
 *                   Sphere
 *
 ******************************************************************************
 */
class Sphere : public SceneObject
{

public:
   Sphere(Vector postion = Vector(0, 0, 0));
   virtual ~Sphere();

public:
   virtual PossibleRayIntersection findIntersectionWith(Ray ray);

protected: // helpers
   PossibleRayIntersection intersectionGivenDistance(Ray ray, double distance);

private:
   double radius_;
};

#endif
