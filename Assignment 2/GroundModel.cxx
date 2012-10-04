
// System
#include <OpenGl.h>

// Qt
#include <QGLWidget>

// Project
#include <GroundModel.h>
#include <RenderHelpers.h>

using namespace RenderHelpers;

const int SIZE = 100;

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
void GroundModel::renderMesh()
{
   glPushMatrix();
   glTranslatev(Vector(0, 0, zPosition_));

   glColor3f(1, 1, 1);

   glEnable(GL_TEXTURE_2D);

   texture_.bind();

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

   glFlush();
   glDisable(GL_TEXTURE_2D);

   glPopMatrix();
}

void GroundModel::renderNormals()
{
   // Do nothing
}

/**
 ******************************************************************************
 *
 *                   Accessors
 *
 ******************************************************************************
 */
Vector GroundModel::center()
{
   return Vector(0, 0, zPosition_);   
}

Vector GroundModel::size()
{
   return Vector(SIZE, SIZE, 0);
}
