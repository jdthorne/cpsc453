#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

// System

// Project
#include <RayIntersection.h>

/**
 ******************************************************************************
 *
 *                   SceneObject
 *
 * This is an abstract base class representing an object in a scene
 *
 ******************************************************************************
 */
class SceneObject
{

public:
   SceneObject(Vector position, Material material);
   virtual ~SceneObject();

public:
   virtual PossibleRayIntersection findIntersectionWith(Ray ray) = 0;

protected: // helpers
   double smallestPositiveValue(double a, double b);

protected: // members
   Vector origin_;
   Material material_;
};

#endif
