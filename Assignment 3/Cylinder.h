#ifndef CYLINDER_H
#define CYLINDER_H

// System

// Project
#include <SceneObject.h>
#include <PropertyList.h>

/**
 ******************************************************************************
 *
 *                   Cylinder
 *
 ******************************************************************************
 */
class Cylinder : public SceneObject
{

public:
   Cylinder(Vector position, double height, double radius, Material material);
   virtual ~Cylinder();

   static Cylinder* newFromFile(PropertyList properties);

public:
   virtual PossibleRayIntersection findIntersectionWith(Ray ray);

private: // helpers

private: // members
   double height_;
   double radius_;

   Vector axis_;
};

#endif
