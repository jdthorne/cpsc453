
// System

// Project
#include <Cylinder.h>

Cylinder::Cylinder(Vector position, double height, double radius, Material material)
   : Group(position, material)
   , height_(height)
   , radius_(radius)
{
}

Cylinder::~Cylinder()
{
}
