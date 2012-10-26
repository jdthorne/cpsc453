#ifndef RENDERHELPERS
#define RENDERHELPERS

// System
#include <OpenGl.h>

// Qt
#include <QImage>
#include <QString>

// Assignment
#include <Vector.h>
#include <AffineMatrix.h>

/**
 ******************************************************************************
 *
 *                   RenderHelpers
 *
 *  This namespace contains additional OpenGL functions which work with 
 *  Vector and AffineMatrix, instead of just doubles and floats.
 *
 ******************************************************************************
 */
namespace RenderHelpers
{
   double wrap(double min, double value, double max);
   double toDeg(double rad);
   double toRad(double deg);

   // Hand-written transformation functions
   void jdRotateaa(double angle, Vector axis);
   void jdRotatea(const AffineMatrix rotation);
   void jdTranslatev(const Vector translation);
   void jdScalev(const Vector scale);
   void jdMultMatrixa(AffineMatrix matrix);

   // Hand-written view functions
   void jdLookAt(Vector eyePosition, Vector lookAtPosition, Vector upDirection);
   void jdPerspective(double fovy, double aspect, double zNear, double zFar);
   void jdOrtho(double left, double right, double bottom, double top, double zNear, double zFar);

   void jdCommitMatrix();

   void jdVertexv(const Vector vertex);
   void jdNormalv(const Vector normal);

   void jdLoadIdentity();
   void jdPushMatrix();
   void jdPopMatrix();

   void jdSetCalculationMode(bool useHandWritten);
}

#endif
