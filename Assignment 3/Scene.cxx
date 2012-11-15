
// System

// Project
#include <Scene.h>
#include <Sphere.h>
#include <Triangle.h>

Scene::Scene()
{
   //objects_.append(new Sphere(Vector(-10, 0, 5), Material::redSteel()));
   objects_.append(new Sphere(Vector(0, 0, 0), Material::blueSteel()));
   objects_.append(new Triangle(Vector(0, 5, 0), 
                                Vector(10, 5, 0),
                                Vector(0, 5, 10),
                                Material::steel()));
   lights_.append(new Light());
}

Scene::~Scene()
{
}

QList<SceneObject*>& Scene::objects()
{
   return objects_;
}

QList<Light*>& Scene::lights()
{
   return lights_;
}

PossibleRayIntersection Scene::findFirstIntersection(Ray ray)
{
   PossibleRayIntersection bestIntersection = PossibleRayIntersection::noIntersection();

   foreach (SceneObject* object, objects_)
   {
      PossibleRayIntersection possibleIntersection = object->findIntersectionWith(ray);

      if (possibleIntersection.exists() && possibleIntersection.intersection().distance() > 0.01)
      {
         if (!bestIntersection.exists())
         {
            bestIntersection = possibleIntersection;
         }
         else if (possibleIntersection.intersection().distance()
                  < bestIntersection.intersection().distance())
         {
            bestIntersection = possibleIntersection;
         }
      }
   }

   return bestIntersection;
}
