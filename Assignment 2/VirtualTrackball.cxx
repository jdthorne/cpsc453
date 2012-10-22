
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

void VirtualTrackball::handleScreenResize(double width, double height)
{
   width_ = width;
   height_ = height;
}

void VirtualTrackball::handleClick(double x, double y)
{
   lastGrabPoint_ = pointFromClick(width_ - x, y);
}

AffineMatrix VirtualTrackball::rotationAfterDragTo(AffineMatrix initialRotation, double x, double y)
{
   TrackballPoint grabPoint = pointFromClick(width_ - x, y);

   if ((grabPoint - lastGrabPoint_).magnitude() < 0.00001)
   {
      return initialRotation;
   }

   Vector rotationVector = grabPoint.cross(lastGrabPoint_);

   // Make the angle larger to rotate faster
   double rotationAngle = rotationVector.magnitude() * 2.4;
   Vector rotationAxis = rotationVector.normalized();

   lastGrabPoint_ = grabPoint;

   return AffineMatrix::fromAxisAngle(rotationAxis, rotationAngle) * initialRotation;
}

TrackballPoint VirtualTrackball::pointFromClick(double x, double y)
{
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

