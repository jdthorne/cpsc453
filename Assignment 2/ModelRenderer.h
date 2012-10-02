#ifndef MD2RENDERER_H
#define MD2RENDERER_H

// System

// Qt
#include <QObject>
#include <QMap>

// Project
#include <I_RenderOptions.h>
#include <Vector.h>
#include <Model.h>

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
   void render();

public: // I_RenderOptions
   virtual void setRenderMode(RenderMode mode);
   virtual void setTranslation(Vector translation);
   virtual void setDisplayNormals(bool displayNormals);

signals:
   void optionsChanged();

private: // helpers
   void setupRenderMode();
   void setupEyePosition();
   void setupTransformation();

   void renderModel(Model& model);
   void renderNormalsIfNecessary(Model& model);

private: // settings
   Vector translation_;
   RenderMode renderMode_;
   bool displayNormals_;

private: // members
   QList<Model*> models_;
};

#endif
