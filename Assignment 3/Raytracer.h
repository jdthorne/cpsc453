#ifndef RAYTRACER_H
#define RAYTRACER_H

// System

// Qt
#include <QImage>

// Project
#include <Scene.h>
#include <Color.h>

/**
 ******************************************************************************
 *
 *                   Raytracer
 *
 ******************************************************************************
 */
class Raytracer
{

public:
   Raytracer();
   virtual ~Raytracer();

public:
   QImage run();

private: // helpers
   Color trace(Ray ray);

   Color traceInitialRay(int x, int y);

   Color totalDirectLightAt(RayIntersection intersection);
   Color totalReflectedLightAt(RayIntersection intersection);

   Color diffuseLightAt(RayIntersection intersection, const SceneLight& light);
   Color specularLightAt(RayIntersection intersection, const SceneLight& light);

private: // members
   Scene scene_;

   Vector cameraPosition_;

   int imageWidth_;
   int imageHeight_;
};

#endif
