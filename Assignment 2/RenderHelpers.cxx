
// System
#include <OpenGl.h>

// Qt
#include <QGLWidget>
#include <QStack>

// Assignment
#include <RenderHelpers.h>

/**
 ******************************************************************************
 *
 *                   Custom Matrix Stack
 *
 ******************************************************************************
 */
AffineMatrix currentMatrix;
QStack<AffineMatrix> matrixStack;

/**
 ******************************************************************************
 *
 *                   Wrap a value to fit within bounds
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

/**
 ******************************************************************************
 *
 *                   Convert between degrees and radians
 *
 ******************************************************************************
 */
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
 *                   Perform an OpenGL rotation with hand-written matricies
 *
 ******************************************************************************
 */
void RenderHelpers::jdRotateaa(double angle, Vector axis)
{
   jdMultMatrixa(AffineMatrix::fromAxisAngle(axis, angle));
}
void RenderHelpers::jdRotatea(const AffineMatrix rotation)
{
   jdMultMatrixa(rotation);
}

/**
 ******************************************************************************
 *
 *                   Perform an OpenGL translation with hand-written matricies
 *
 ******************************************************************************
 */
void RenderHelpers::jdTranslatev(const Vector vector)
{
   jdMultMatrixa(AffineMatrix::fromTranslationVector(vector));
}

/**
 ******************************************************************************
 *
 *                   Perform an OpenGL scale with hand-written matricies
 *
 ******************************************************************************
 */
void RenderHelpers::jdScalev(const Vector scale)
{
   jdMultMatrixa(AffineMatrix::fromScaleVector(scale));
}

/**
 ******************************************************************************
 *
 *                   Perform a hand-written multiply with the current Gl matrix
 *
 ******************************************************************************
 */
void RenderHelpers::jdMultMatrixa(AffineMatrix multMatrix)
{
   // Multiply it by the paramter
   AffineMatrix newMatrix = currentMatrix * multMatrix;

   // Stuff it back into OpenGL
   jdLoadMatrixa(newMatrix);
}

/**
 ******************************************************************************
 *
 *                   Helper to call glVertex with a Vector
 *
 ******************************************************************************
 */
void RenderHelpers::jdVertexv(const Vector vertex)
{
   glVertex3f(vertex.x, vertex.y, vertex.z);
}

/**
 ******************************************************************************
 *
 *                   Helper to call glNormal with a Vector
 *
 ******************************************************************************
 */
void RenderHelpers::jdNormalv(const Vector vertex)
{
   glNormal3f(vertex.x, vertex.y, vertex.z);
}

/**
 ******************************************************************************
 *
 *                   Load an AffineMatrix into OpenGL
 *
 ******************************************************************************
 */
void RenderHelpers::jdLoadMatrixa(AffineMatrix matrix)
{
   // Create an array of values from the matrix
   GLfloat values[16];

   // Fill the values[] array with the matrix body
   for (int i = 0; i < 4; i++)
   {
      for (int j = 0; j < 4; j++)
      {
         // Matrix element [i][j] ends up at index (i * 4) + j
         int index = (i * 4) + j;
         values[index] = matrix.element[i][j];
      }
   }

   // Load the matrix into OpenGL
   glLoadMatrixf(values);   
}

/**
 ******************************************************************************
 *
 *                   Custom matrix stack
 *
 ******************************************************************************
 */
void RenderHelpers::jdPushMatrix()
{
   matrixStack.push(currentMatrix);
}

void RenderHelpers::jdPopMatrix()
{
   currentMatrix = matrixStack.pop();
}

