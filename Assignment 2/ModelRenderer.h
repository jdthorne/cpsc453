#ifndef MD2RENDERER_H
#define MD2RENDERER_H

// System

// Qt
#include <QObject>
#include <QMap>

// Project
#include <I_RenderOptions.h>
#include <ModelManager.h>
#include <Vector.h>

class Model;
class GroundModel;

/**
 ******************************************************************************
 *
 *                   ModelRenderer
 *
 ******************************************************************************
 */
class ModelRenderer : public I_RenderOptions
{
   Q_OBJECT

public:
   ModelRenderer();
   virtual ~ModelRenderer();

public:
   void initialize();
   void render();

   void setFrameSize(double width, double height);

   I_ModelSelector& modelSelector();

public: // I_RenderOptions
   virtual AffineMatrix rotation();
   virtual Vector eyePosition();
   virtual Vector lookAtPosition();

   virtual void setRenderMode(RenderMode mode);
   virtual void setTranslation(Vector translation);
   virtual void setRotation(AffineMatrix rotation);
   virtual void setScale(Vector scale);
   virtual void setDisplayNormals(bool displayNormals);
   virtual void setProjectionMode(ProjectionMode mode);

   virtual void setEyePosition(Vector position);
   virtual void setLookAtPosition(Vector position);
   virtual void setUpDirection(Vector position);

signals:
   void rotationChanged();
   void eyePositionChanged();
   void lookAtPositionChanged();

   void renderChanged();

private slots:
   void handleModelsChanged();

private: // helpers
   void setupRenderMode();
   void setupProjectionMode();
   void setupEyePosition();
   void setupTransformation();

   void renderModel(Model& model);

private: // settings
   Vector translation_;
   AffineMatrix rotation_;
   Vector scale_;
   RenderMode renderMode_;
   bool displayNormals_;
   ProjectionMode projectionMode_;

   Vector eyePosition_;
   Vector lookAtPosition_;
   Vector upDirection_;

   double width_;
   double height_;

private: // members
   GroundModel* groundModel_;
   
   ModelManager modelManager_;

};

#endif
