
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
   glClearColor(0.0, 0.0, 0.0, 0.0);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

   GLfloat materialSpecular[] = { 0.2, 0.2, 0.2, 1.0 };
   GLfloat materialShininess[] = { 1.0 };
   GLfloat lightPosition[] = { 0, 0, 100.0, 100.0 };
   glShadeModel(GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
   glMaterialfv(GL_BACK, GL_SPECULAR, materialSpecular);
   glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess);
   glMaterialfv(GL_BACK, GL_SHININESS, materialShininess);
   glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

   glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
   glEnable(GL_COLOR_MATERIAL);

   glShadeModel(GL_SMOOTH);
   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
   glClearDepth(1.0);

   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);

   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

   glEnable(GL_SMOOTH);

   resizeGL(width(), height());
}

void OpenGlCore::resizeGL(int width, int height)
{
   glViewport(0, 0, width, height);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(55.0f, (GLfloat)width/(GLfloat)height, 0.1f, 5000.0f);
}

void OpenGlCore::paintGL()
{
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(0, 0, 100, 0, 0, 0, 0, 1, 0);

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glColor3f(1, 0, 0);

   renderer_.render();

   glFlush();
}

