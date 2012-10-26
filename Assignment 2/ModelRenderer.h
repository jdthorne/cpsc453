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
 *  This class renders models to the screen, and allows you to control the
 *  various options through I_RenderOptions.
 *
 ******************************************************************************
 */
class ModelRenderer : public I_RenderOptions
{
   Q_OBJECT

public:
   ModelRenderer(ModelManager& manager);
   virtual ~ModelRenderer();

public:
   void initialize();
   void render();

   void setViewport(int x, int y, int width, int height);

   void configureMainView();
   void configureTopView();
   void configureSideView();
   void configureFrontView();

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

   virtual void forceRedraw();

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

   double distanceRequiredToSeeEntireModel();

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

   int x_;
   int y_;
   int width_;
   int height_;

private: // members
   GroundModel* groundModel_;
   
   ModelManager& modelManager_;

};

#endif
