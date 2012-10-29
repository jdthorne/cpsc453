#ifndef MD2MODEL_H
#define MD2MODEL_H

// 3rdparty
#include <md2.h>

// System

// Qt
#include <QTimer>
#include <QObject>

// Project
#include <Model.h>
#include <OpenGlTexture.h>

/**
 ******************************************************************************
 *
 *                   Md2Model
 *
 *  This class is a wrapper around the MD2 model, as well as its associated
 *  texture.
 *
 ******************************************************************************
 */
class Md2Model : public Model
{
   Q_OBJECT

public:
   Md2Model(QString modelDataFilename, QString skinTextureFilename);
   virtual ~Md2Model();

public: // render functions
   virtual void renderMesh(AlternativeMode mode);
   virtual void renderNormals();

   virtual void resetAnimation();

public: // accessors
   virtual Vector center();
   virtual Vector size();

signals:
   void frameChanged();
   void animationRestarted();

private slots: // animation
   virtual void handleFrameTimeout();

private: // helpers
   void calculateBounds();
   void calculateFaceNormals();
   void calculateVertexNormals();

private: // members
   MD2* data_;
   
   OpenGlTexture texture_;

   QMap<int, Vector> faceNormals_;
   QMap<int, Vector> vertexNormals_;

   Vector center_;
   Vector size_;

   QTimer animationTimer_;
   int currentAnimation_;
   int currentFrame_;
};

#endif
