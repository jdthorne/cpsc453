
// System

// Qt
#include <QtGlobal>

// Project
#include <RaytracerStatus.h>

RaytracerStatus::RaytracerStatus()
   : depth_(0)
   , rayIsInsideObject_(false)
{

}

RaytracerStatus::~RaytracerStatus()
{
}

/**
 ******************************************************************************
 *
 *                   Determine if we're out of depth level
 *
 ******************************************************************************
 */
bool RaytracerStatus::outOfDepth()
{
   return (depth_ > 5);
}

/**
 ******************************************************************************
 *
 *                   Simple accessors
 *
 ******************************************************************************
 */
bool RaytracerStatus::rayIsInsideObject()
{
   return rayIsInsideObject_;
}

/**
 ******************************************************************************
 *
 *                   Return a status for the next recursion
 *
 ******************************************************************************
 */
RaytracerStatus RaytracerStatus::nextRecursion()
{
   RaytracerStatus result = *this;
   result.depth_++;

   return result;
}

/**
 ******************************************************************************
 *
 *                   Return a status for the next recursion, for the
 *                   case of refraction
 *
 ******************************************************************************
 */
RaytracerStatus RaytracerStatus::nextRecursionDueToRefraction()
{
   RaytracerStatus result = *this;

   result.depth_++;
   result.rayIsInsideObject_ = !result.rayIsInsideObject_;

   return result;
}

