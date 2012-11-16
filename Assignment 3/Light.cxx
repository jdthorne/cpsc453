
// System

// Project
#include <Light.h>

Light::Light(Vector position, Color color)
   : position_(position)
   , color_(color)
{
}

Light* Light::newFromFile(PropertyList properties)
{
   return new Light(properties.vector("Position"),
                    properties.color("Color"));
}

Light::~Light()
{
}

Vector Light::position() const
{
   return position_;
}

Color Light::color() const
{
   return color_;
}
