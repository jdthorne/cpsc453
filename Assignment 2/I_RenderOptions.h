#ifndef I_RENDEROPTIONS_H
#define I_RENDEROPTIONS_H

// System

// Project
#include <Vector.h>

enum RenderMode
{
   Wireframe,
   FlatShading,
   SmoothShading
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
   virtual void setDisplayNormals(bool displayNormals) = 0;

public: // signals
   virtual void optionsChanged() = 0;

};

#endif
