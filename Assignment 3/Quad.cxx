
// System

// Project
#include <Quad.h>
#include <Triangle.h>

Quad::Quad(Vector p1, Vector p2, Vector p3, Vector p4, Material material)
   : Group( QList<SceneObject*>() << new Triangle(p1, p2, p4, material)
                                  << new Triangle(p2, p3, p4, material),
           p1,
           material)
{

}

Quad::~Quad()
{
}

