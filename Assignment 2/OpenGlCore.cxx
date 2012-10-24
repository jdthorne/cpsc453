
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
   // Configure the material settings
   GLfloat materialSpecular[] = { 0.2, 0.2, 0.2, 1.0 };
   GLfloat materialShininess[] = { 1.0 };
   glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
   glMaterialfv(GL_BACK, GL_SPECULAR, materialSpecular);
   glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess);
   glMaterialfv(GL_BACK, GL_SHININESS, materialShininess);

   // Configure the light
   GLfloat ambientLight[] = { 0.5, 0.5, 0.5, 1.0 };
   GLfloat lightPosition[] = { 0, 0, 100.0, 100.0 };
   glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
   glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);

   // Enable the light
   glEnable(GL_LIGHT0);

   // Enable material coloring
   glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
   glEnable(GL_COLOR_MATERIAL);

   // Default to smooth shading
   glShadeModel(GL_SMOOTH);

   // Set the background to be gray
   glClearColor(0.4f, 0.4f, 0.4f, 0.0f);
   glClearDepth(1.0);

   // Turn on depth testing
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);

   // Set the perspective correction hint
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

   // Enable alpha blending
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   // Initialize the renderer
   renderer_.initialize();

   // Ensure the canvas is sized properly
   resizeGL(width(), height());
}

/**
 ******************************************************************************
 *
 *                   Handle OpenGL resizing
 *
 ******************************************************************************
 */
void OpenGlCore::resizeGL(int width, int height)
{
   // Set the GL viewport
   jdViewport(0, 0, width, height);

   // Notify children who care
   renderer_.setFrameSize(width, height);
   trackball_.handleScreenResize(width, height);
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
   // Clear the screen
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // Render everything
   renderer_.render();

   // Flush GL
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
   // Forward to trackball
   trackball_.handleClick(event->x(), event->y());
}

void OpenGlCore::mouseMoveEvent(QMouseEvent* event)
{
   // Ask trackball to calculate the new rotation
   AffineMatrix rotation = renderer_.rotation();
   AffineMatrix newRotation = trackball_.rotationAfterDragTo(rotation, event->x(), event->y());

   renderer_.setRotation(newRotation);
}

/**
 ******************************************************************************
 *
 *                   Mouse Wheel Handling - zoom in/out
 *
 ******************************************************************************
 */
void OpenGlCore::wheelEvent(QWheelEvent* event)
{
   // Figure out how far to zoom
   double distance = qBound(-40, event->delta(), 40) * 0.5;

   // Figure out the vector from the eye, to the look-at point
   Vector fromEyeToLookAt = (renderer_.lookAtPosition() - renderer_.eyePosition()).normalized();

   // Move the eye along that vector
   Vector eyeMovement = (fromEyeToLookAt * distance);
   Vector newEyePosition = renderer_.eyePosition() + eyeMovement;

   // If the new position is too close, put the eye at the boundary instead
   if ((newEyePosition - renderer_.lookAtPosition()).magnitude() < 50)
   {
      renderer_.setEyePosition(renderer_.lookAtPosition() + (fromEyeToLookAt * -50));
      return;
   }

   // Set the new eye position
   renderer_.setEyePosition(newEyePosition);
}