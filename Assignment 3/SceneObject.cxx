
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
