
// System

// Project
#include <Light.h>

Light::Light()
   : position_(10, 0, 15)
{

}

Light::~Light()
{
}

Vector Light::position() const
{
   return position_;
}
