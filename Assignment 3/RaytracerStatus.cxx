
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

bool RaytracerStatus::outOfDepth()
{
   return (depth_ > 5);
}

bool RaytracerStatus::rayIsInsideObject()
{
   return rayIsInsideObject_;
}

RaytracerStatus RaytracerStatus::nextRecursion()
{
   RaytracerStatus result = *this;
   result.depth_++;

   return result;
}

RaytracerStatus RaytracerStatus::nextRecursionDueToRefraction()
{
   RaytracerStatus result = *this;

   result.depth_++;
   result.rayIsInsideObject_ = !result.rayIsInsideObject_;

   return result;
}

