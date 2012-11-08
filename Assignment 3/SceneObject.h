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
 ******************************************************************************
 */
class SceneObject
{

public:
   SceneObject(Vector position, Material material);
   virtual ~SceneObject();

public:
   virtual PossibleRayIntersection findIntersectionWith(Ray ray) = 0;

protected: // members
   Vector center_;
   Material material_;
};

#endif
