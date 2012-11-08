
// System

// Project
#include <SceneObject.h>

SceneObject::SceneObject(Vector position, Material material)
   : center_(position)
   , material_(material)
{

}

SceneObject::~SceneObject()
{
}
