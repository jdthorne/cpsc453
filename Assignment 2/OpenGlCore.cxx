
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
   : modelManager_()
   , mainRenderer_(modelManager_)
   , frontRenderer_(modelManager_)
   , sideRenderer_(modelManager_)
   , topRenderer_(modelManager_)
   , renderManager_(&mainRenderer_, QList<I_RenderOptions*>() << &frontRenderer_
                                                              << &sideRenderer_
                                                              << &topRenderer_)
{
   // Ensure that we repaint if we need to
   connect(&mainRenderer_, SIGNAL(renderChanged()), this, SLOT(handleRenderChanged()));
   connect(&frontRenderer_, SIGNAL(renderChanged()), this, SLOT(handleRenderChanged()));
   connect(&sideRenderer_, SIGNAL(renderChanged()), this, SLOT(handleRenderChanged()));
   connect(&topRenderer_, SIGNAL(renderChanged()), this, SLOT(handleRenderChanged()));

   // Make sure we setup our cameras as needed
   connect(&modelManager_, SIGNAL(modelsChanged()), this, SLOT(handleModelsChanged()));
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

   // Set the background color
   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
   glClearDepth(1.0);

   // Turn on depth testing
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);

   // Set the perspective correction hint
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

   // Enable alpha blending
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   // Initialize the renderers
   mainRenderer_.initialize();
   frontRenderer_.initialize();
   sideRenderer_.initialize();
   topRenderer_.initialize();
   modelManager_.loadDefaultModelSet();

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
   QGLWidget::resizeGL(width, height);
   trackball_.handleScreenResize(width, height);

   // Configure the viewports 
   int xDivision = (width / 4);
   int yDivision = (height / 4);

   topRenderer_.setViewport(0, 0, xDivision, yDivision);
   frontRenderer_.setViewport(0, yDivision, xDivision, height - yDivision);
   sideRenderer_.setViewport(xDivision, 0, width - xDivision, yDivision);
   mainRenderer_.setViewport(xDivision, yDivision, width - xDivision, height - yDivision);
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
   topRenderer_.render();
   frontRenderer_.render();
   sideRenderer_.render();
   mainRenderer_.render();

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
   return renderManager_;
}

I_ModelSelector& OpenGlCore::modelSelector()
{
   return modelManager_;
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
   AffineMatrix rotation = renderManager_.rotation();
   AffineMatrix newRotation = trackball_.rotationAfterDragTo(rotation, event->x(), event->y());

   renderManager_.setRotation(newRotation);
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
   Vector fromEyeToLookAt = (mainRenderer_.lookAtPosition() - mainRenderer_.eyePosition()).normalized();

   // Move the eye along that vector
   Vector eyeMovement = (fromEyeToLookAt * distance);
   Vector newEyePosition = mainRenderer_.eyePosition() + eyeMovement;

   // If the new position is too close, put the eye at the boundary instead
   if ((newEyePosition - mainRenderer_.lookAtPosition()).magnitude() < 50)
   {
      mainRenderer_.setEyePosition(mainRenderer_.lookAtPosition() + (fromEyeToLookAt * -50));
      return;
   }

   // Set the new eye position
   mainRenderer_.setEyePosition(newEyePosition);
}

/**
 ******************************************************************************
 *
 *                   Handle changes in models by auto-configuring
 *                   the four viewports
 *
 ******************************************************************************
 */
void OpenGlCore::handleModelsChanged()
{
   mainRenderer_.configureMainView();
   frontRenderer_.configureFrontView();
   topRenderer_.configureTopView();
   sideRenderer_.configureSideView();
}

