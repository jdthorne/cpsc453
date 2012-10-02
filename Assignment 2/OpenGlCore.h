#ifndef OPENGLCORE_H
#define OPENGLCORE_H

// System

// Qt
#include <QGLWidget>

// Project
#include <Md2Renderer.h>

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

private: // helpers

private: // members
   Md2Renderer renderer_;
};

#endif
