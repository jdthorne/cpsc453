#ifndef RAYTRACER_H
#define RAYTRACER_H

// System

// Qt
#include <QImage>

// Project
#include <Scene.h>
#include <Color.h>

#include <RaytracerStatus.h>

/**
 ******************************************************************************
 *
 *                   Raytracer
 *
 * This class handles the core raytracing functions.  It requires a scene,
 * and performs raytracing in an interative manner.  To use it, call
 * run() as long as running() returns true.
 *
 ******************************************************************************
 */
class Raytracer
{

public:
   Raytracer(Scene& scene);
   virtual ~Raytracer();

public:
   bool running();
   QImage run();

private: // helpers
   Color trace(Ray ray, RaytracerStatus status = RaytracerStatus());

   Color traceInitialRay(int x, int y);

   Color totalDirectLightAt(RayIntersection intersection);
   Color totalReflectedLightAt(RayIntersection intersection, RaytracerStatus status);
   Color totalRefractedLightAt(RayIntersection intersection, RaytracerStatus status);

   Color ambientLightAt(RayIntersection intersection);
   Color diffuseLightAt(RayIntersection intersection, const Light& light);
   Color specularLightAt(RayIntersection intersection, const Light& light);

private: // members
   Scene& scene_;
   QImage result_;

   Vector cameraPosition_;

   int imageWidth_;
   int imageHeight_;

   int y_;
};

#endif
