
// System
#include <OpenGl.h>

// Qt
#include <QGLWidget>

// Assignment
#include <RenderHelpers.h>

/**
 ******************************************************************************
 *
 *                   Misc Helpers
 *
 ******************************************************************************
 */
double RenderHelpers::wrap(double min, double value, double max)
{
   while (value < min)
   {
      value += (max - min);
   }

   while (value > max)
   {
      value -= (max - min);
   }

   return value;
}


double RenderHelpers::toDeg(double rad)
{
   return (rad * 180) / 3.1415926535;
}

double RenderHelpers::toRad(double deg)
{
   return (deg / 180) * 3.1415926535;
}

/**
 ******************************************************************************
 *
 *                   Vector- and Euler- versions of standard functions
 *
 ******************************************************************************
 */
void RenderHelpers::glRotatee(const Euler rotation)
{
   glRotatef(toDeg(rotation.roll), 0, 0, 1);
   glRotatef(toDeg(rotation.pitch), 1, 0, 0);
   glRotatef(toDeg(rotation.yaw), 0, 1, 0);
}

void RenderHelpers::glVertexv(const Vector vertex)
{
   glVertex3f(vertex.x, vertex.y, vertex.z);
}

void RenderHelpers::glTranslatev(const Vector vertex)
{
   glTranslatef(vertex.x, vertex.y, vertex.z);
}

void RenderHelpers::glNormalv(const Vector vertex)
{
   glNormal3f(vertex.x, vertex.y, vertex.z);
}

void RenderHelpers::glScalev(const Vector scale)
{
   glScalef(scale.x, scale.y, scale.z);
}

/**
 ******************************************************************************
 *
 *                   Fancy Helpers
 *
 ******************************************************************************
 */
void RenderHelpers::glBillboard()
{
   float modelView[16];
   glGetFloatv(GL_MODELVIEW_MATRIX, modelView);

   for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++)
   {
      modelView[i*4 + j] = (i == j ? 1.0 : 0.0);
   }
   glLoadMatrixf(modelView);
}

void RenderHelpers::glSphere(const Vector position, double scale)
{
   glPushMatrix();

   glTranslatev(position);

   glBillboard();

   glScalef(scale, scale, scale);
   glBegin(GL_QUADS);

   glTexCoord2d(0.0, 0.0); glVertex2d(-1.0, -1.0);
   glTexCoord2d(1.0, 0.0); glVertex2d(1.0, -1.0);
   glTexCoord2d(1.0, 1.0); glVertex2d(1.0, 1.0);
   glTexCoord2d(0.0, 1.0); glVertex2d(-1.0, 1.0);

   glEnd();
   glPopMatrix();
}

