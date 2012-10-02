#ifndef MD2RENDERER_H
#define MD2RENDERER_H

// System

// 3rdparty
#include <md2.h>

// Qt
#include <QObject>
#include <QMap>

// Project
#include <I_RenderOptions.h>
#include <Vector.h>

/**
 ******************************************************************************
 *
 *                   Md2Renderer
 *
 ******************************************************************************
 */
class Md2Renderer : public QObject, public I_RenderOptions
{
   Q_OBJECT

public:
   Md2Renderer();
   virtual ~Md2Renderer();

public:
   void render();

public: // I_RenderOptions
   virtual void setRenderMode(RenderMode mode);
   virtual void setTranslation(Vector translation);
   virtual void setDisplayNormals(bool displayNormals);

signals:
   void optionsChanged();

private: // helpers
   void calculateFaceNormals();
   void calculateVertexNormals();

   void setupRenderMode();
   void renderTriangle(triangle_t& triangle);

private: // settings
   Vector translation_;
   RenderMode renderMode_;
   bool displayNormals_;

private: // members
   MD2* model_; 

   QMap<int, Vector> faceCenters_;
   QMap<int, Vector> faceNormals_;
   QMap<int, Vector> vertexNormals_;
};

#endif
