
// System
#include <cmath>

// Project
#include <VirtualTrackball.h>

VirtualTrackball::VirtualTrackball()
{

}

VirtualTrackball::~VirtualTrackball()
{
}

/**
 ******************************************************************************
 *
 *                   Store the screen size (to convert mouse coords to sphere coords)
 *
 ******************************************************************************
 */
void VirtualTrackball::handleScreenResize(double width, double height)
{
   width_ = width;
   height_ = height;
}

/**
 ******************************************************************************
 *
 *                   Remember where the initial click was
 *
 ******************************************************************************
 */
void VirtualTrackball::handleClick(double x, double y)
{
   lastGrabPoint_ = pointFromClick(width_ - x, y);
}

/**
 ******************************************************************************
 *
 *                   Calculate the rotation when the mouse is dragged
 *
 ******************************************************************************
 */
AffineMatrix VirtualTrackball::rotationAfterDragTo(AffineMatrix initialRotation, double x, double y)
{
   // Figure out the grab point
   TrackballPoint grabPoint = pointFromClick(width_ - x, y);

   // Don't do anything if the magnitude is zero (otherwise cross product will explode)
   if ((grabPoint - lastGrabPoint_).magnitude() < 0.00001)
   {
      return initialRotation;
   }

   // Figure out the rotation vector
   Vector rotationVector = grabPoint.cross(lastGrabPoint_);

   // Convert into angle/axis format
   double rotationAngle = rotationVector.magnitude();
   Vector rotationAxis = rotationVector.normalized();

   // Make the angle larger so we spin faster
   rotationAngle *= 2.4;

   // Save the grab point for next time
   lastGrabPoint_ = grabPoint;

   // Figure out how much we just rotate
   AffineMatrix newRotation = AffineMatrix::fromAxisAngle(rotationAxis, rotationAngle);

   // Return the total rotation
   return (newRotation * initialRotation);
}

/**
 ******************************************************************************
 *
 *                   Figure out the sphere point from mouse coordinates
 *
 ******************************************************************************
 */
TrackballPoint VirtualTrackball::pointFromClick(double x, double y)
{  
   // Adapted from Erika Harrison's tutorial notes
   // http://pages.cpsc.ucalgary.ca/~eharris/cpsc453/tut09/
   double ySphere = (x / width_) * 2.0 - 1.0;
   double zSphere = (y / height_) * 2.0 - 1.0;

   double yzSquared = ySphere*ySphere + zSphere*zSphere;
   double xSphere = 0.0;
   if (yzSquared < 1.0)
   {
      xSphere = sqrt(1.0 - yzSquared);
   }

   return Vector(xSphere, ySphere, zSphere);
}

