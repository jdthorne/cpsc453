
// System

// Project
#include <SceneLight.h>

SceneLight::SceneLight()
   : position_(25, 0, 15)
{

}

SceneLight::~SceneLight()
{
}

Vector SceneLight::position() const
{
   return position_;
}

