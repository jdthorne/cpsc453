#ifndef SCENELIGHT_H
#define SCENELIGHT_H

// System

// Project
#include <Vector.h>

/**
 ******************************************************************************
 *
 *                   Light
 *
 ******************************************************************************
 */
class Light
{

public:
   Light();
   virtual ~Light();

public:
   Vector position() const;

private: // helpers

private: // members
   Vector position_;
};

#endif
