#ifndef RAY_H
#define RAY_H

// System

// Project
#include <Vector.h>

/**
 ******************************************************************************
 *
 *                   Ray
 *
 * This class represents a tracable ray, starting from a point, and continuing
 * in a direction.
 *
 ******************************************************************************
 */
class Ray
{
   Ray(Vector start, Vector direction);

public:
   virtual ~Ray();

   static Ray fromStartAndDirection(Vector start, Vector direction);
   static Ray fromPointToPoint(Vector from, Vector to);

public:
   Vector start();
   Vector direction();

private: // members
   Vector start_;
   Vector direction_;
};

#endif
