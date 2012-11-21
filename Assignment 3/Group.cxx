
// System

// Project
#include <Group.h>

Group::Group(Vector position, Material material)
   : SceneObject(position, material)
{

}

Group::Group(QList<SceneObject*> children, Vector position, Material material)
   : SceneObject(position, material)
   , children_(children)
{

}

Group::~Group()
{
   while (children_.count() > 0)
   {
      SceneObject* child = children_.first();
      children_.removeFirst();
      
      delete child;
   }
}

/**
 ******************************************************************************
 *
 *                   Find the intersection with any member of the group
 *
 ******************************************************************************
 */
PossibleRayIntersection Group::findIntersectionWith(Ray ray)
{
   PossibleRayIntersection bestIntersection = PossibleRayIntersection::noIntersection();

   foreach (SceneObject* object, children_)
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

/**
 ******************************************************************************
 *
 *                   Add new object to the group
 *
 ******************************************************************************
 */
void Group::addObject(SceneObject* object)
{
   children_.append(object);
}

