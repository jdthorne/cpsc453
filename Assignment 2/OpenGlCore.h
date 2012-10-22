#ifndef OPENGLCORE_H
#define OPENGLCORE_H

// System

// Qt
#include <QGLWidget>

// Project
#include <ModelRenderer.h>
#include <I_RenderOptions.h>
#include <I_ModelSelector.h>

class QMouseEvent;

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

protected:
   void mousePressEvent(QMouseEvent* event);
   void mouseMoveEvent(QMouseEvent* event);

   void wheelEvent(QWheelEvent* event);

private slots:
   void handleRenderChanged();

private: // helpers

private: // members
   double xInitialMouse_;
   double yInitialMouse_;

   ModelRenderer renderer_;
};

#endif
