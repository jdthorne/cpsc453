
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

bool useHandWrittenTransformations = false;

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
   if (useHandWrittenTransformations)
   {
      jdMultMatrixa(AffineMatrix::fromAxisAngle(axis, angle));
   }
   else
   {
      glRotatef(toDeg(angle), axis.x, axis.y, axis.z);
   }
}
void RenderHelpers::jdRotatea(const AffineMatrix rotation)
{
   if (useHandWrittenTransformations)
   {
      jdMultMatrixa(rotation);
   }
   else
   {
      GLfloat values[16] = AFFINE_TO_GL(rotation);
      glMultMatrixf(values);
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
   if (useHandWrittenTransformations)
   {
      jdMultMatrixa(AffineMatrix::fromTranslationVector(vector));
   }
   else
   {
      glTranslatef(vector.x, vector.y, vector.z);
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
   if (useHandWrittenTransformations)
   {
      jdMultMatrixa(AffineMatrix::fromScaleVector(scale));
   }
   else
   {
      glScalef(scale.x, scale.y, scale.z);
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
   if (useHandWrittenTransformations)
   {
      currentMatrix = currentMatrix * multMatrix;
   }
   else
   {
      GLfloat values[16] = AFFINE_TO_GL(multMatrix);
      glMultMatrixf(values);
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
 *                   Custom matrix stack
 *
 ******************************************************************************
 */
void RenderHelpers::jdLoadIdentity()
{
   if (useHandWrittenTransformations)
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
   if (useHandWrittenTransformations)
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
   if (useHandWrittenTransformations)
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
   if (useHandWrittenTransformations)
   {
      GLfloat values[16] = AFFINE_TO_GL(currentMatrix);
      glLoadMatrixf(values);
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
   if (useHandWrittenTransformations)
   {
      // This math is based on the man page for gluLookAt
      //    $ man gluLookAt

      Vector f = (lookAtPosition - eyePosition).normalized();
      Vector upPrime = upDirection.normalized();

      Vector s = f.cross(upPrime);
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
 *                   Allow setting the calculation mode
 *
 ******************************************************************************
 */
void RenderHelpers::jdSetCalculationMode(bool useHandWritten)
{
   useHandWrittenTransformations = useHandWritten;
}

