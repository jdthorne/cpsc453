
// System

// Project
#include <MathHelpers.h>

double bound(double min, double value, double max)
{
   if (value < min)
   {
      return min;
   };

   if (value > max)
   {
      return max;
   }

   return value;
}

unsigned char floor(double value)
{
   return (unsigned char)value;
}
