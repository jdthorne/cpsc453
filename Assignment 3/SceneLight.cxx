
// System

// Project
#include <SceneLight.h>

SceneLight::SceneLight()
   : position_(50, 0, 50)
{

}

SceneLight::~SceneLight()
{
}

Vector SceneLight::position() const
{
   return position_;
}

