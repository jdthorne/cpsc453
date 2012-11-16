#ifndef CYLINDER_H
#define CYLINDER_H

// System

// Project
#include <Group.h>

/**
 ******************************************************************************
 *
 *                   Cylinder
 *
 ******************************************************************************
 */
class Cylinder : public Group
{

public:
   Cylinder(Vector position, double height, double radius, Material material);
   virtual ~Cylinder();

public:

private: // helpers

private: // members
   double height_;
   double radius_;
};

#endif
