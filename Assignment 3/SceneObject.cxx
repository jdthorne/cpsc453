
// System

// Project
#include <SceneObject.h>

SceneObject::SceneObject(Vector position, Material material)
   : origin_(position)
   , material_(material)
{

}

SceneObject::~SceneObject()
{
}

/**
 ******************************************************************************
 *
 *                   Return smallest non-zero positive value
 *
 ******************************************************************************
 */
double SceneObject::smallestPositiveValue(double a, double b)
{
   if (a < 0.0000001)
   {
      return b;
   }
   else if (b < 0.0000001)
   {
      return a;
   }
   else if (a < b)
   {
      return a;
   }
   return b;
}

