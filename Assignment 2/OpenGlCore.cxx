
// System

// Project
#include <OpenGlCore.h>
#include <OpenGl.h>

OpenGlCore::OpenGlCore()
{

}

OpenGlCore::~OpenGlCore()
{
}

void OpenGlCore::initializeGL()
{
   glClearColor(0, 0, 0, 0);
   //glEnable(GL_DEPTH_TEST);
}

void OpenGlCore::resizeGL(int width, int height)
{
   glViewport(0, 0, width, height);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(55.0f, (GLfloat)width/(GLfloat)height, 0.1f, 5000.0f);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
}

void OpenGlCore::paintGL()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glColor3f(1, 0, 0);

   renderer_.render();

   glFlush();
}

