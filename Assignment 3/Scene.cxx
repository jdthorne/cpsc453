
// System

// Project
#include <Scene.h>
#include <Sphere.h>

Scene::Scene()
{
   objects_.append(new Sphere());
}

Scene::~Scene()
{
}

QList<SceneObject*>& Scene::objects()
{
   return objects_;
}

