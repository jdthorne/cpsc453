
// System

// Project
#include <Scene.h>
#include <Sphere.h>
#include <Quad.h>

Scene::Scene()
   : root_(Vector(0, 0, 0), Material::none())
{
   root_.addObject(new Sphere(Vector(0, 0, 0), Material::blueSteel()));
   //root_.addObject(new Triangle(Vector(0, 5, 0), 
   //                             Vector(10, 5, 0),
   //                             Vector(0, 5, 10),
   //                             Material::steel()));

   root_.addObject(new Quad(Vector(-10, 5, -10),
                            Vector(+10, 5, -10),
                            Vector(+10, 5, +10),
                            Vector(-10, 5, +10),
                            Material::steel()));

   lights_.append(new Light());
}

Scene::~Scene()
{
}

QList<Light*>& Scene::lights()
{
   return lights_;
}

PossibleRayIntersection Scene::findFirstIntersection(Ray ray)
{
   return root_.findIntersectionWith(ray);
}
