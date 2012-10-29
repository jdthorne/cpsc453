
// System
#include <OpenGl.h>

// Qt
#include <QGLWidget>

// Project
#include <GroundModel.h>
#include <RenderHelpers.h>

using namespace RenderHelpers;

const int SIZE = 250;

GroundModel::GroundModel()
   : texture_("ground.jpg")
   , zPosition_(0)
{
}

GroundModel::~GroundModel()
{
}

/**
 ******************************************************************************
 *
 *                   Setup
 *
 ******************************************************************************
 */
void GroundModel::setZPosition(double z)
{
   zPosition_ = z;
}

/**
 ******************************************************************************
 *
 *                   Actual Render Functions
 *
 ******************************************************************************
 */
void GroundModel::renderMesh(AlternativeMode mode)
{
   // Ignore the alternative mode
   Q_UNUSED(mode);

   // Setup the matrix
   jdPushMatrix();
   jdTranslatev(Vector(0, 0, zPosition_));
   jdCommitMatrix();

   // Setup the color
   glColor3f(1, 1, 1);

   // Enable the texture
   glEnable(GL_TEXTURE_2D);
   texture_.bind();

   // Draw the four quads
   glBegin(GL_QUADS);

      glNormal3f(0, 0, 1);

      glTexCoord2f(0, 0);
      glVertex3f(-SIZE/2, -SIZE/2, 0);

      glTexCoord2f(1, 0);
      glVertex3f(+SIZE/2, -SIZE/2, 0);

      glTexCoord2f(1, 1);
      glVertex3f(+SIZE/2, +SIZE/2, 0);

      glTexCoord2f(0, 1);
      glVertex3f(-SIZE/2, +SIZE/2, 0);

   glEnd();

   // Flush the coordinates
   glFlush();

   // Disable the texture
   glDisable(GL_TEXTURE_2D);

   // Pop our matrix changes
   jdPopMatrix();
}

void GroundModel::renderNormals()
{
   // Do nothing
}

/**
 ******************************************************************************
 *
 *                   Get the model's center
 *
 ******************************************************************************
 */
Vector GroundModel::center()
{
   return Vector(0, 0, zPosition_);   
}

/**
 ******************************************************************************
 *
 *                   Get the model's size
 *
 ******************************************************************************
 */
Vector GroundModel::size()
{
   return Vector(SIZE, SIZE, 0);
}

/**
 ******************************************************************************
 *
 *                   The ground model isn't animated, so do nothing
 *
 ******************************************************************************
 */
void GroundModel::resetAnimation()
{
   // The ground model isn't animated, so do nothing
}

