
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
 *                   Vector- and Matrix- versions of standard functions
 *
 ******************************************************************************
 */
void RenderHelpers::glRotateaa(double angle, Vector axis)
{
   glMultMatrixa(AffineMatrix::fromAxisAngle(axis, angle));
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
 *                   Matrix Helpers
 *
 ******************************************************************************
 */
AffineMatrix RenderHelpers::glGetMatrix(GLenum matrixMode)
{
   AffineMatrix result;

   GLfloat values[16];
   glGetFloatv(matrixMode, values);

   for (int i = 0; i < 4; i++)
   {
      for (int j = 0; j < 4; j++)
      {
         int cell = (i * 4) + j;
         result.element[i][j] = values[cell];
      }
   }

   return result;
}

void RenderHelpers::glLoadMatrixa(AffineMatrix matrix)
{
   GLfloat values[16];

   for (int i = 0; i < 4; i++)
   {
      for (int j = 0; j < 4; j++)
      {
         int cell = (i * 4) + j;
         values[cell] = matrix.element[i][j];
      }
   }

   glLoadMatrixf(values);   
}

void RenderHelpers::glMultMatrixa(AffineMatrix multMatrix)
{
   AffineMatrix currentMatrix = glGetMatrix(GL_MODELVIEW_MATRIX);
   AffineMatrix newMatrix = currentMatrix * multMatrix;

   glLoadMatrixa(newMatrix);
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

