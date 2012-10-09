#ifndef OPENGLCORE_H
#define OPENGLCORE_H

// System

// Qt
#include <QGLWidget>

// Project
#include <ModelRenderer.h>
#include <I_RenderOptions.h>
#include <I_ModelSelector.h>

/**
 ******************************************************************************
 *
 *                   OpenGlCore
 *
 ******************************************************************************
 */
class OpenGlCore : public QGLWidget
{
   Q_OBJECT

public:
   OpenGlCore();
   ~OpenGlCore();

public:
   virtual void initializeGL();
   virtual void resizeGL(int width, int height);
   virtual void paintGL();

   I_RenderOptions& renderOptions();
   I_ModelSelector& modelSelector();

private slots:
   void handleRenderOptionsChanged();

private: // helpers

private: // members
   ModelRenderer renderer_;
};

#endif
