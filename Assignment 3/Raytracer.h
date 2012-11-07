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
   Color traceInitialRay(int x, int y);

   Color trace(Ray ray);

private: // members
   Scene scene_;

   int imageWidth_;
   int imageHeight_;
};

#endif
