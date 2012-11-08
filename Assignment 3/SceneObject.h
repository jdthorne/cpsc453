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
   SceneObject(Vector position);
   virtual ~SceneObject();

public:
   virtual PossibleRayIntersection findIntersectionWith(Ray ray) = 0;

protected: // members
   Vector center_;

};

#endif
