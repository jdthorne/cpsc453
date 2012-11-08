
// System

// Project
#include <RayIntersection.h>

RayIntersection::RayIntersection(Ray incomingRay, double distance,
                                 Vector surfaceNormal, Material material)
   : incomingRay_(incomingRay)
   , distance_(distance)
   , surfaceNormal_(surfaceNormal)

   , intersectionPoint_(incomingRay_.start() + (incomingRay_.direction() * distance_))
   , reflectedRay_(calculateReflection())

   , material_(material)
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

Material RayIntersection::material()
{
   return material_;
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

   return Ray::fromStartAndDirection(start, direction);
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
   RayIntersection nullIntersection = RayIntersection(Ray::fromPointToPoint(Vector(), Vector()), 999999, Vector(), Material::none());
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

