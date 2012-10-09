
// System

// Project
#include <I_ModelSelector.h>
#include <RenderHelpers.h>
#include <OpenGlCore.h>
#include <OpenGl.h>

using namespace RenderHelpers;

OpenGlCore::OpenGlCore()
{
   connect(&renderer_, SIGNAL(renderChanged()), this, SLOT(handleRenderOptionsChanged()));
}

OpenGlCore::~OpenGlCore()
{
}

void OpenGlCore::initializeGL()
{
   glEnable(GL_LIGHT0);

   GLfloat ambientLight[] = { 0.5, 0.5, 0.5, 1.0 };
   GLfloat materialSpecular[] = { 0.2, 0.2, 0.2, 1.0 };
   GLfloat materialShininess[] = { 1.0 };
   GLfloat lightPosition[] = { 0, 0, 100.0, 100.0 };
   glShadeModel(GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
   glMaterialfv(GL_BACK, GL_SPECULAR, materialSpecular);
   glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess);
   glMaterialfv(GL_BACK, GL_SHININESS, materialShininess);
   glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
   glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);

   glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
   glEnable(GL_COLOR_MATERIAL);

   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
   glClearDepth(1.0);

   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);

   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   renderer_.initialize();

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
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glColor3f(1, 0, 0);

   renderer_.render();

   glFlush();
}

I_RenderOptions& OpenGlCore::renderOptions()
{
   return renderer_;
}

void OpenGlCore::handleRenderOptionsChanged()
{
   update();
}

I_ModelSelector& OpenGlCore::modelSelector()
{
   return renderer_.modelSelector();
}

