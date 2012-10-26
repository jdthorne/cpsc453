#ifndef OPENGLCORE_H
#define OPENGLCORE_H

// System

// Qt
#include <QGLWidget>

// Project
#include <VirtualTrackball.h>
#include <ModelRenderer.h>
#include <I_RenderOptions.h>
#include <I_ModelSelector.h>
#include <RenderOptionManager.h>

class QMouseEvent;

/**
 ******************************************************************************
 *
 *                   OpenGlCore
 *
 *  This class is the core QGLWidget, which is responsible for delegating
 *  input handling and rendering.
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

protected:
   void mousePressEvent(QMouseEvent* event);
   void mouseMoveEvent(QMouseEvent* event);

   void wheelEvent(QWheelEvent* event);

private slots:
   void handleRenderChanged();
   void handleModelsChanged();

private: // helpers

private: // members
   VirtualTrackball trackball_;

   ModelManager modelManager_;

   ModelRenderer mainRenderer_;
   ModelRenderer frontRenderer_;
   ModelRenderer sideRenderer_;
   ModelRenderer topRenderer_;
   RenderOptionManager renderManager_;
};

#endif
