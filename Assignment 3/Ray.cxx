
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

Ray Ray::fromTo(Vector from, Vector to)
{
   Vector direction = (to - from);
   return Ray(from, direction);
}

Ray Ray::startDirection(Vector start, Vector direction)
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

