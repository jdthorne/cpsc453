#ifndef GROUP_H
#define GROUP_H

// System

// Project
#include <SceneObject.h>

/**
 ******************************************************************************
 *
 *                   Group
 *
 * Represents a set of SceneObjects which have been "glued" together into
 * one SceneObject.
 *
 ******************************************************************************
 */
class Group : public SceneObject
{

public:
   Group(Vector position, Material material);
   Group(QList<SceneObject*> children, Vector position, Material material);
   virtual ~Group();

public:
   virtual PossibleRayIntersection findIntersectionWith(Ray ray);

   void addObject(SceneObject* object);

private: // helpers

private: // members
   QList<SceneObject*> children_;
};

#endif
