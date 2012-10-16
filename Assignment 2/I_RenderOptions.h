#ifndef I_RENDEROPTIONS_H
#define I_RENDEROPTIONS_H

// System

// Project
#include <Vector.h>
#include <Quaternion.h>

enum RenderMode
{
   Wireframe,
   FlatShading,
   SmoothShading
};

enum ProjectionMode
{
   Perspective,
   Parallel
};

/**
 ******************************************************************************
 *
 *                   I_RenderOptions
 *
 ******************************************************************************
 */
class I_RenderOptions
{

public:
   virtual ~I_RenderOptions() {};

public:
   virtual void setRenderMode(RenderMode mode) = 0;
   virtual void setTranslation(Vector translation) = 0;
   virtual void setRotation(Quaternion rotation) = 0;
   virtual void setScale(Vector scale) = 0;
   virtual void setDisplayNormals(bool displayNormals) = 0;
   virtual void setProjectionMode(ProjectionMode mode) = 0;

};

#endif
