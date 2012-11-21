#ifndef QUAD_H
#define QUAD_H

// System

// Project
#include <Group.h>
#include <PropertyList.h>

/**
 ******************************************************************************
 *
 *                   Quad
 *
 * This class represents a quad, by gluing two triangles together in a group
 *
 ******************************************************************************
 */
class Quad : public Group
{

public:
   Quad(Vector p1, Vector p2, Vector p3, Vector p4, Material material);
   virtual ~Quad();

   static Quad* newFromFile(PropertyList properties);

public:

private: // helpers

private: // members

};

#endif
