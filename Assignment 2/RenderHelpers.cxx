
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
      // Hand written "rotate" == hand written multiply by axis/angle affine matrix
      jdMultMatrixa(AffineMatrix::fromAxisAngle(axis, angle));
   }
   else
   {
      // Delegate to OpenGL
      glRotated(toDeg(angle), axis.x, axis.y, axis.z);
   }
}
void RenderHelpers::jdRotatea(const AffineMatrix rotation)
{
   if (useHandWrittenMath)
   {
      // Hand written "rotate" == hand written multiply by rotation
      jdMultMatrixa(rotation);
   }
   else
   {  
      // Delegate to OpenGL
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
      // Hand written "translate" == hand written multiply by Affine translation matrix
      jdMultMatrixa(AffineMatrix::fromTranslationVector(vector));
   }
   else
   {
      // Delegate to OpenGL
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
      // Hand written "scale" == hand written multiply by Affine scale matrix
      jdMultMatrixa(AffineMatrix::fromScaleVector(scale));
   }
   else
   {
      // Delegate to OpenGL
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
      // Multiply current matrix by multMatrix
      currentMatrix = currentMatrix * multMatrix;
   }
   else
   {
      // Delegate to OpenGL
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
   // Stuff a Vector into an OpenGL vertex() call
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
   // Stuff a Vector into an OpenGL normal() call
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
      // Make the currentMatrix be the identity matrix
      currentMatrix = AffineMatrix::identity();
   }
   else
   {
      // Delegate to OpenGL
      glLoadIdentity();
   }
}

void RenderHelpers::jdPushMatrix()
{
   if (useHandWrittenMath)
   {
      // Push the current matrix onto the stack
      matrixStack.push(currentMatrix);
   }
   else 
   {
      // Delegate to OpenGL
      glPushMatrix();
   }
}

void RenderHelpers::jdPopMatrix()
{
   if (useHandWrittenMath)
   {
      // Pop the current matrix from the stack
      currentMatrix = matrixStack.pop();
   }
   else
   {
      // Delegate to OpenGL
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
      // Printout, so we can tell useHandWrittenMath is enabled
      qDebug("[RenderHelpers] Committing Hand-Written Math to OpenGL");

      // Load the matrix into OpenGL
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
      upDirection.normalize();

      // Calculate forward, side and up vectors
      Vector forward = (lookAtPosition - eyePosition).normalized();

      Vector side = f.cross(upDirection).normalized();
      Vector up = s.cross(f);
   
      // Stuff them into an AffineMatrix
      AffineMatrix m = AffineMatrix::identity();
      m.element[0][0] = side.x;
      m.element[1][0] = side.y;
      m.element[2][0] = side.z;

      m.element[0][1] = up.x;
      m.element[1][1] = up.y;
      m.element[2][1] = up.z;

      m.element[0][2] = -forward.x;
      m.element[1][2] = -forward.y;
      m.element[2][2] = -forward.z;

      m.element[3][3] = 1.0;

      // Apply the matrix
      jdMultMatrixa(m);

      // Move by the eye position
      jdTranslatev(eyePosition * -1);
   }
   else 
   {
      // Delegate to OpenGL
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
      // Precalculate factor 'f'
      double f = 1.0 / tan(toRad(fovy) / 2.0);

      // Load values into AffineMatrix
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
      // Delegate to OpenGL
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
      AffineMatrix m = AffineMatrix::identity();

      // Load clipping volume into AffineMatrix      
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
      // Delegate to OpenGL
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

