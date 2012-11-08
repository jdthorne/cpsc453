
// System

// Project
#include <SceneLight.h>

SceneLight::SceneLight()
   : position_(5, 0, 5)
{

}

SceneLight::~SceneLight()
{
}

Vector SceneLight::position() const
{
   return position_;
}

