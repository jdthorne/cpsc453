#ifndef RAYINTERSECTION_H
#define RAYINTERSECTION_H

// System

// Qt
#include <QPair>

// Project
#include <Ray.h>
#include <Vector.h>
#include <Material.h>

/**
 ******************************************************************************
 *
 *                   RayIntersection
 *
 * This class represents a ray intersecting an object, consiting of the
 * incoming ray, intersection point, surface normal, and surface material
 *
 ******************************************************************************
 */
class RayIntersection
{

public:
   RayIntersection(Ray incomingRay, double distance,
                   Vector surfaceNormal, Material material);
   virtual ~RayIntersection();

public: // accessors
   Ray incomingRay();
   Ray reflectedRay();
   double distance();

   Vector point();
   Vector surfaceNormal();
   Material material();

private: // helpers
   Ray calculateReflection();

private:
   Ray incomingRay_;
   double distance_;

   Vector surfaceNormal_;

   Vector intersectionPoint_;
   Ray reflectedRay_;

   Material material_;
};

/**
 ******************************************************************************
 *
 *                   Possible Ray Intersection
 *
 * This class represents a "maybe" value for Ray, similar to a null pointer,
 * but in an entirely memory safe manner.
 *
 ******************************************************************************
 */
class PossibleRayIntersection
{

public:
   PossibleRayIntersection(RayIntersection intersection);
   virtual ~PossibleRayIntersection();

   static PossibleRayIntersection noIntersection();

public:
   bool exists();
   RayIntersection intersection();

private:
   bool exists_;
   RayIntersection intersection_;
};

#endif
