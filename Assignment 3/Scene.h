#ifndef SCENE_H
#define SCENE_H

// System

// Qt
#include <QList>

// Project
#include <SceneObject.h>

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

private: // helpers

private: // members
   QList<SceneObject*> objects_;

};

#endif
