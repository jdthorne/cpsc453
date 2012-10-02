#ifndef MODEL_H
#define MODEL_H

// 3rdparty
#include <md2.h>

// Qt
#include <QMap>

// System

// Project
#include <Vector.h>

/**
 ******************************************************************************
 *
 *                   Model
 *
 ******************************************************************************
 */
class Model
{
public:
   Model(QString filename);
   ~Model();

   MD2& data();
   QMap<int, Vector>& faceCenters();
   QMap<int, Vector>& faceNormals();
   QMap<int, Vector>& vertexNormals();

   Vector& center();
   Vector& size();

private: // helpers
   void calculateBounds();
   void calculateFaceNormals();
   void calculateVertexNormals();

private: // members
   MD2* md2Data_;

   QMap<int, Vector> faceCenters_;
   QMap<int, Vector> faceNormals_;
   QMap<int, Vector> vertexNormals_;

   Vector center_;
   Vector size_;
};

#endif
