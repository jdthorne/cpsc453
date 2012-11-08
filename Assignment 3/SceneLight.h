#ifndef SCENELIGHT_H
#define SCENELIGHT_H

// System

// Project
#include <Vector.h>

/**
 ******************************************************************************
 *
 *                   SceneLight
 *
 ******************************************************************************
 */
class SceneLight
{

public:
   SceneLight();
   virtual ~SceneLight();

public:
   Vector position() const;

private: // helpers

private: // members
   Vector position_;
};

#endif
