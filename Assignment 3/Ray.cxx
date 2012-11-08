
// System

// Project
#include <Ray.h>

Ray::Ray(Vector start, Vector direction)
   : start_(start)
   , direction_(direction.normalized())
{
}

Ray::~Ray()
{
}

Ray Ray::fromPointToPoint(Vector from, Vector to)
{
   Vector direction = (to - from);
   return Ray(from, direction);
}

Ray Ray::fromStartAndDirection(Vector start, Vector direction)
{
   return Ray(start, direction);
}

Vector Ray::start()
{
   return start_;
}

Vector Ray::direction()
{
   return direction_;
}

