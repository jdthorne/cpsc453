
// System

// Qt
#include <QMouseEvent>
#include <qmath.h>

// Project
#include <I_ModelSelector.h>
#include <RenderHelpers.h>
#include <OpenGlCore.h>
#include <OpenGl.h>

using namespace RenderHelpers;

OpenGlCore::OpenGlCore()
{
   connect(&renderer_, SIGNAL(renderChanged()), this, SLOT(handleRenderChanged()));
}

OpenGlCore::~OpenGlCore()
{
}

/**
 ******************************************************************************
 *
 *                   OpenGL Setup
 *
 ******************************************************************************
 */
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

   glClearColor(0.4f, 0.4f, 0.4f, 0.0f);
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
   renderer_.setFrameSize(width, height);
}

/**
 ******************************************************************************
 *
 *                   OpenGL Painting
 *
 ******************************************************************************
 */
void OpenGlCore::handleRenderChanged()
{
   update();
}

void OpenGlCore::paintGL()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   renderer_.render();

   glFlush();
}


/**
 ******************************************************************************
 *
 *                   Accessors
 *
 ******************************************************************************
 */
I_RenderOptions& OpenGlCore::renderOptions()
{
   return renderer_;
}

I_ModelSelector& OpenGlCore::modelSelector()
{
   return renderer_.modelSelector();
}

/**
 ******************************************************************************
 *
 *                   Mouse Handling
 *
 ******************************************************************************
 */
void OpenGlCore::mousePressEvent(QMouseEvent* event)
{
   xInitialMouse_ = event->x();
   yInitialMouse_ = event->y();
}

void OpenGlCore::mouseMoveEvent(QMouseEvent* event)
{
   double xDelta = (event->x() - xInitialMouse_);
   double yDelta = (event->y() - yInitialMouse_);

   Euler rotation = renderer_.rotation();
   rotation.roll = wrap(-M_PI, rotation.roll + toRad(xDelta), M_PI);
   rotation.yaw = wrap(-M_PI, rotation.yaw + toRad(yDelta), M_PI);
   renderer_.setRotation(rotation);

   xInitialMouse_ = event->x();
   yInitialMouse_ = event->y();
}

void OpenGlCore::wheelEvent(QWheelEvent* event)
{
   Vector fromEyeToLookAt = (renderer_.lookAtPosition() - renderer_.eyePosition()).normalized();
   Vector eyeMovement = (fromEyeToLookAt * event->delta());
   Vector newEyePosition = renderer_.eyePosition() + eyeMovement;

   if (newEyePosition.magnitude() > 1000 || newEyePosition.magnitude() < (2 * event->delta()) || newEyePosition.magnitude() < 20)
   {
      return;
   }

   renderer_.setEyePosition(newEyePosition);
}