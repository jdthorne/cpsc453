
// System
#include <cmath>
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

bool useHandWrittenMath = false;

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
   if (useHandWrittenMath)
   {
      jdMultMatrixa(AffineMatrix::fromAxisAngle(axis, angle));
   }
   else
   {
      glRotated(toDeg(angle), axis.x, axis.y, axis.z);
   }
}
void RenderHelpers::jdRotatea(const AffineMatrix rotation)
{
   if (useHandWrittenMath)
   {
      jdMultMatrixa(rotation);
   }
   else
   {
      GLdouble values[16] = AFFINE_TO_GL(rotation);
      glMultMatrixd(values);
   }
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
   if (useHandWrittenMath)
   {
      jdMultMatrixa(AffineMatrix::fromTranslationVector(vector));
   }
   else
   {
      glTranslated(vector.x, vector.y, vector.z);
   }
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
   if (useHandWrittenMath)
   {
      jdMultMatrixa(AffineMatrix::fromScaleVector(scale));
   }
   else
   {
      glScaled(scale.x, scale.y, scale.z);
   }
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
   if (useHandWrittenMath)
   {
      currentMatrix = currentMatrix * multMatrix;
   }
   else
   {
      GLdouble values[16] = AFFINE_TO_GL(multMatrix);
      glMultMatrixd(values);
   }
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
   glVertex3d(vertex.x, vertex.y, vertex.z);
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
   glNormal3d(vertex.x, vertex.y, vertex.z);
}

/**
 ******************************************************************************
 *
 *                   Custom matrix stack
 *
 ******************************************************************************
 */
void RenderHelpers::jdLoadIdentity()
{
   if (useHandWrittenMath)
   {
      currentMatrix = AffineMatrix::identity();
   }
   else
   {
      glLoadIdentity();
   }
}

void RenderHelpers::jdPushMatrix()
{
   if (useHandWrittenMath)
   {
      matrixStack.push(currentMatrix);
   }
   else 
   {
      glPushMatrix();
   }
}

void RenderHelpers::jdPopMatrix()
{
   if (useHandWrittenMath)
   {
      currentMatrix = matrixStack.pop();
   }
   else
   {
      glPopMatrix();
   }
}

/**
 ******************************************************************************
 *
 *                   Actually commit the matrix to OpenGL
 *
 ******************************************************************************
 */
void RenderHelpers::jdCommitMatrix()
{
   if (useHandWrittenMath)
   {
      GLdouble values[16] = AFFINE_TO_GL(currentMatrix);
      glLoadMatrixd(values);
   }
   else
   {
      // OpenGL already has the matrix, so don't screw it up :)
   }
}

/**
 ******************************************************************************
 *
 *                   Custom implementation of OpenGL look at function
 *
 ******************************************************************************
 */
void RenderHelpers::jdLookAt(Vector eyePosition, Vector lookAtPosition, Vector upDirection)
{
   if (useHandWrittenMath)
   {
      // This math is adapted from the man page for gluLookAt
      //    $ man gluLookAt

      Vector f = (lookAtPosition - eyePosition).normalized();
      Vector upPrime = upDirection.normalized();

      Vector s = f.cross(upPrime).normalized();
      Vector u = s.cross(f);

      AffineMatrix m = AffineMatrix::identity();
      m.element[0][0] = s.x;
      m.element[1][0] = s.y;
      m.element[2][0] = s.z;

      m.element[0][1] = u.x;
      m.element[1][1] = u.y;
      m.element[2][1] = u.z;

      m.element[0][2] = -f.x;
      m.element[1][2] = -f.y;
      m.element[2][2] = -f.z;

      m.element[3][3] = 1.0;

      jdMultMatrixa(m);
      jdTranslatev(eyePosition * -1);
   }
   else 
   {
      gluLookAt(eyePosition.x, eyePosition.y, eyePosition.z,
                lookAtPosition.x, lookAtPosition.y, lookAtPosition.z,
                upDirection.x, upDirection.y, upDirection.z);
   }
}

/**
 ******************************************************************************
 *
 *                   Custom gluPerspective implementation
 *
 ******************************************************************************
 */
void RenderHelpers::jdPerspective(double fovy, double aspect, double zNear, double zFar)
{
   if (useHandWrittenMath)
   {
      // This math is adapted from the man page for gluPerspective
      //    $ man gluPerspective

      double f = 1.0 / tan(toRad(fovy) / 2.0);
      AffineMatrix m = AffineMatrix::identity();
      
      m.element[0][0] = f / aspect;
      m.element[1][1] = f;
      m.element[2][2] = (zFar + zNear) / (zNear - zFar);
      m.element[3][3] = 0.0;

      m.element[3][2] = (2 * zFar * zNear) / (zNear - zFar);
      m.element[2][3] = -1;

      // Save the matrix on our custom stack
      currentMatrix = m;
   }
   else
   {
      gluPerspective(fovy, aspect, zNear, zFar);
   }
}

/**
 ******************************************************************************
 *
 *                   Custom glOrtho implementation
 *
 ******************************************************************************
 */
void RenderHelpers::jdOrtho(double left, double right, double bottom, double top, double zNear, double zFar)
{
   if (useHandWrittenMath)
   {
      // This math is adapted from the man page for glOrtho
      //    $ man glOrtho

      AffineMatrix m = AffineMatrix::identity();
      
      m.element[0][0] = 2 / (right - left);
      m.element[1][1] = 2 / (top - bottom);
      m.element[2][2] = -2 / (zFar - zNear);
      m.element[3][3] = 1.0;

      m.element[3][0] = -(right + left) / (right - left);
      m.element[3][1] = -(top + bottom) / (top - bottom);
      m.element[3][2] = -(zFar + zNear) / (zFar - zNear);

      // Save the matrix on our custom stack
      currentMatrix = m;
   }
   else
   {
      glOrtho(left, right, bottom, top, zNear, zFar);
   }
}

/**
 ******************************************************************************
 *
 *                   Allow setting the calculation mode
 *
 ******************************************************************************
 */
void RenderHelpers::jdSetCalculationMode(bool handWritten)
{
   useHandWrittenMath = handWritten;
}

