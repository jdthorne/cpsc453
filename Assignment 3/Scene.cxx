
// System

// Project
#include <Scene.h>
#include <Sphere.h>
#include <Triangle.h>

Scene::Scene()
{
   objects_.append(new Sphere(Vector(0, 5, 0), Material::redSteel()));
   objects_.append(new Sphere(Vector(0, -5, 0), Material::blueSteel()));
   objects_.append(new Triangle(Vector(0, 10, 0), 
                                Vector(10, 10, 0),
                                Vector(0, 10, 10),
                                Material::steel()));
   lights_.append(new SceneLight());
}

Scene::~Scene()
{
}

QList<SceneObject*>& Scene::objects()
{
   return objects_;
}

QList<SceneLight*>& Scene::lights()
{
   return lights_;
}

PossibleRayIntersection Scene::findFirstIntersection(Ray ray)
{
   PossibleRayIntersection bestIntersection = PossibleRayIntersection::noIntersection();

   foreach (SceneObject* object, objects_)
   {
      PossibleRayIntersection possibleIntersection = object->findIntersectionWith(ray);

      if (possibleIntersection.exists())
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


/**
 ******************************************************************************
 *
 *                   So, the scene right now is:
 *                
 *        Sphere is at (0, 0, 0)
 *        Camera is at (0, 0, 100), looking along -Z
 *        Light is at  (25, 25, 50)
 *
 ******************************************************************************
 */