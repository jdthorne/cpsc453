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
   Color trace(Ray ray, RaytracerStatus status = RaytracerStatus());

   Color traceInitialRay(int x, int y);

   Color totalDirectLightAt(RayIntersection intersection);
   Color totalReflectedLightAt(RayIntersection intersection, RaytracerStatus status);
   Color totalRefractedLightAt(RayIntersection intersection, RaytracerStatus status);

   Color ambientLightAt(RayIntersection intersection);
   Color diffuseLightAt(RayIntersection intersection, const Light& light);
   Color specularLightAt(RayIntersection intersection, const Light& light);

private: // members
   Scene scene_;

   Vector cameraPosition_;

   int imageWidth_;
   int imageHeight_;
};

#endif
