
// System

// Project
#include <Scene.h>
#include <Sphere.h>
#include <Quad.h>

Scene::Scene()
   : root_(Vector(0, 0, 0), Material::none())
{
   root_.addObject(new Sphere(Vector(0, 0, 0), Material::glass()));
   root_.addObject(new Sphere(Vector(10, 0, 0), Material::bluePlastic()));
   root_.addObject(new Sphere(Vector(-10, 0, 0), Material::redSteel()));

   root_.addObject(new Sphere(Vector(0, 0, -15), Material::yellowPlastic()));

   root_.addObject(new Quad(Vector(-20, 5, -20),
                            Vector(+20, 5, -20),
                            Vector(+20, 5, +20),
                            Vector(-20, 5, +20),
                            Material::steel()));

   //lights_.append(new Light(Vector(15, -5, 25), Color(0.3, 0.3, 0.3)));
   //lights_.append(new Light(Vector(-15, -5, 25), Color(0.3, 0.3, 0.3)));
   lights_.append(new Light(Vector(0, -25, 0), Color(0.6, 0.6, 0.6)));
   lights_.append(new Light(Vector(0, 0, 10), Color(0.6, 0.6, 0.6)));
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
