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
class ModelRenderer : public QObject, public I_RenderOptions
{
   Q_OBJECT

public:
   ModelRenderer();
   virtual ~ModelRenderer();

public:
   void initialize();
   void render();

   I_ModelSelector& modelSelector();

public: // I_RenderOptions
   virtual void setRenderMode(RenderMode mode);
   virtual void setTranslation(Vector translation);
   virtual void setRotation(Quaternion rotation);
   virtual void setScale(Vector scale);
   virtual void setDisplayNormals(bool displayNormals);

signals:
   void renderChanged();

private: // helpers
   void setupRenderMode();
   void setupEyePosition();
   void setupTransformation();

   void renderModel(Model& model);

private: // settings
   Vector translation_;
   Quaternion rotation_;
   Vector scale_;
   RenderMode renderMode_;
   bool displayNormals_;

private: // members
   GroundModel* groundModel_;
   
   ModelManager modelManager_;
};

#endif
