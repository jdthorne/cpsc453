#ifndef TRIANGLE_H
#define TRIANGLE_H

// System

// Project
#include <Vector.h>
#include <SceneObject.h>

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
   Triangle(Vector position, Vector pointTwo, Vector pointThree, Material material);
   virtual ~Triangle();

public:
   virtual PossibleRayIntersection findIntersectionWith(Ray ray);

private: // helpers

private: // members
   Vector pointTwo_;
   Vector pointThree_;

   Vector normal_;
};

#endif
