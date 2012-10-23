#ifndef VIRTUALTRACKBALL_H
#define VIRTUALTRACKBALL_H

// System

// Project
#include <AffineMatrix.h>
#include <Vector.h>

/**
 ******************************************************************************
 *
 *                   VirtualTrackball
 *
 *  This class implements the Virtual Trackball algorithm, adapted from
 *  http://pages.cpsc.ucalgary.ca/~eharris/cpsc453/tut09/
 *
 ******************************************************************************
 */
typedef Vector TrackballPoint;

class VirtualTrackball
{

public:
   VirtualTrackball();
   virtual ~VirtualTrackball();

public:
   void handleScreenResize(double width, double height);

   void handleClick(double x, double y);
   AffineMatrix rotationAfterDragTo(AffineMatrix initialRotation, double x, double y);

private: // helpers
   TrackballPoint pointFromClick(double x, double y);

private: // members
   double width_;
   double height_;

   TrackballPoint lastGrabPoint_;
};

#endif
