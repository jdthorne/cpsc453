#ifndef SCENELIGHT_H
#define SCENELIGHT_H

// System

// Project
#include <Vector.h>
#include <Color.h>

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
   Light(Vector position, Color color);
   virtual ~Light();

public:
   Vector position() const;
   Color color() const;

private: // helpers

private: // members
   Vector position_;
   Color color_;
};

#endif
