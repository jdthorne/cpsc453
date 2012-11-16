#ifndef TRIANGLE_H
#define TRIANGLE_H

// System

// Project
#include <Vector.h>
#include <SceneObject.h>
#include <PropertyList.h>

/**
 ******************************************************************************
 *
 *                   Triangle
 *
 ******************************************************************************
 */
class Triangle : public SceneObject
{

public:
   Triangle(Vector p1, Vector p2, Vector p3, Material material);
   virtual ~Triangle();
   static Triangle* newFromFile(PropertyList properties);

public:
   virtual PossibleRayIntersection findIntersectionWith(Ray ray);

private: // helpers

private: // members
   Vector p1_;
   Vector p2_;
   Vector p3_;

   Vector normal_;
};

#endif
