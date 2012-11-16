#ifndef SCENE_H
#define SCENE_H

// System

// Qt
#include <QList>

// Project
#include <SceneObject.h>
#include <Light.h>
#include <Group.h>

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
   QList<Light*>& lights();

   PossibleRayIntersection findFirstIntersection(Ray ray);

private: // helpers
   void loadFromFile(QString filename);
   void addObjectFromFile(QString type, QString properties);

private: // members
   Group root_;
   QList<Light*> lights_;

};

#endif
