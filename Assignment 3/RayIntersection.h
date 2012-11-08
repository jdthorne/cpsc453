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
