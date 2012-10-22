
// System
#include <cmath>

// Project
#include <Euler.h>

Euler::Euler()
   : roll(0)
   , pitch(0)
   , yaw(0)
{
}

Euler::Euler(double roll, double pitch, double yaw)
   : roll(roll)
   , pitch(pitch)
   , yaw(yaw)
{
}

Euler::~Euler()
{
}

Euler Euler::fromAffineMatrix(AffineMatrix matrix)
{
   Euler result;

   //result.roll = atan2(-matrix.element[0][2], sqrt(matrix.element[1][2]*matrix.element[1][2] + matrix.element[2][2]*matrix.element[2][2]));
   result.roll = atan2(matrix.element[2][0], matrix.element[1][1]);
   result.pitch = atan2(matrix.element[1][2], matrix.element[2][2]);
   result.yaw = atan2(matrix.element[0][1], matrix.element[0][0]);

   return result;
}
