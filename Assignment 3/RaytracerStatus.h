#ifndef RAYTRACERSTATUS_H
#define RAYTRACERSTATUS_H

// System

// Project

/**
 ******************************************************************************
 *
 *                   RaytracerStatus
 *
 ******************************************************************************
 */
class RaytracerStatus
{

public:
   RaytracerStatus();
   virtual ~RaytracerStatus();

public:
   bool outOfDepth();
   bool rayIsInsideObject();

   RaytracerStatus nextRecursion();
   RaytracerStatus nextRecursionDueToRefraction();

private: // helpers

private: // members
   int depth_;
   bool rayIsInsideObject_;
};

#endif
