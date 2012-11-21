#ifndef SCENELIGHT_H
#define SCENELIGHT_H

// System

// Project
#include <Vector.h>
#include <Color.h>
#include <PropertyList.h>

/**
 ******************************************************************************
 *
 *                   Light
 *
 * Represents a dynamic point light in the scene, defined by a position and
 * a color
 *
 ******************************************************************************
 */
class Light
{

public:
   Light(Vector position, Color color);
   virtual ~Light();

   static Light* newFromFile(PropertyList properties);

public:
   Vector position() const;
   Color color() const;

private: // helpers

private: // members
   Vector position_;
   Color color_;
};

#endif
