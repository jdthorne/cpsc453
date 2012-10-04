#ifndef MD2MODEL_H
#define MD2MODEL_H

// 3rdparty
#include <md2.h>

// System

// Project
#include <Model.h>

/**
 ******************************************************************************
 *
 *                   Md2Model
 *
 ******************************************************************************
 */
class Md2Model : public Model
{

public:
   Md2Model(QString modelDataFilename, QString skinTextureFilename);
   virtual ~Md2Model();

public: // render functions
   virtual void renderMesh();
   virtual void renderNormals();

public: // accessors
   virtual Vector center();
   virtual Vector size();

private: // helpers
   void calculateBounds();
   void calculateFaceNormals();
   void calculateVertexNormals();

private: // members
   MD2* data_;
   
   GLuint texture_;
   int textureWidth_;
   int textureHeight_;

   QMap<int, Vector> faceCenters_;
   QMap<int, Vector> faceNormals_;
   QMap<int, Vector> vertexNormals_;

   Vector center_;
   Vector size_;

};

#endif
