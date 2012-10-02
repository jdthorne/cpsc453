#ifndef MD2RENDERER_H
#define MD2RENDERER_H

// System

// Qt
#include <QMap>

// Project
#include <Vector.h>
#include <md2.h>

/**
 ******************************************************************************
 *
 *                   Md2Renderer
 *
 ******************************************************************************
 */
class Md2Renderer
{

public:
   Md2Renderer();
   ~Md2Renderer();

public:
   void render();

private: // helpers
   void calculateFaceNormals();
   void calculateVertexNormals();

   void renderTriangle(triangle_t& triangle);

private: // members
   MD2* model_; 

   QMap<int, Vector> faceNormals_;
   QMap<int, Vector> vertexNormals_;
};

#endif
