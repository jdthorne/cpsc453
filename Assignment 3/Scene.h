#ifndef SCENE_H
#define SCENE_H

// System

// Qt
#include <QList>

// Project
#include <SceneObject.h>
#include <SceneLight.h>

/**
 ******************************************************************************
 *
 *                   Scene
 *
 ******************************************************************************
 */
class Scene
{

public:
   Scene();
   virtual ~Scene();

public:
   QList<SceneObject*>& objects();
   QList<SceneLight*>& lights();

   PossibleRayIntersection findFirstIntersection(Ray ray);

private: // helpers

private: // members
   QList<SceneObject*> objects_;
   QList<SceneLight*> lights_;

};

#endif
