
// System

// Project
#include <RayIntersection.h>

RayIntersection::RayIntersection(Ray incomingRay, double distance,
                                 Vector surfaceNormal)
   : incomingRay_(incomingRay)
   , distance_(distance)
   , surfaceNormal_(surfaceNormal)

   , intersectionPoint_(incomingRay_.start() + (incomingRay_.direction() * distance_))
   , reflectedRay_(calculateReflection())
{
}

RayIntersection::~RayIntersection()
{
}

/**
 ******************************************************************************
 *
 *                   Accessors
 *
 ******************************************************************************
 */
Ray RayIntersection::incomingRay()
{
   return incomingRay_;
}

Ray RayIntersection::reflectedRay()
{
   return reflectedRay_;
}

double RayIntersection::distance()
{
   return distance_;
}

Vector RayIntersection::surfaceNormal()
{
   return surfaceNormal_;
}

Vector RayIntersection::point()
{
   return intersectionPoint_;
}

/**
 ******************************************************************************
 *
 *                   Calculations
 *
 ******************************************************************************
 */
Ray RayIntersection::calculateReflection()
{
   Vector start = intersectionPoint_;
   Vector direction = incomingRay_.direction().reflected(surfaceNormal_);

   return Ray::startDirection(start, direction);
}

/**
 ******************************************************************************
 *
 *                   Possible Ray Intersection
 *
 ******************************************************************************
 */
PossibleRayIntersection PossibleRayIntersection::noIntersection()
{
   RayIntersection nullIntersection = RayIntersection(Ray::fromTo(Vector(), Vector()), 999999, Vector());
   PossibleRayIntersection result = PossibleRayIntersection(nullIntersection);
   result.exists_ = false;

   return result;
}


PossibleRayIntersection::PossibleRayIntersection(RayIntersection intersection)
   : exists_(true)
   , intersection_(intersection)
{
}
PossibleRayIntersection::~PossibleRayIntersection()
{
}
bool PossibleRayIntersection::exists()
{
   return exists_;
}

RayIntersection PossibleRayIntersection::intersection()
{
   return intersection_;
}

