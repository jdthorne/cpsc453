#ifndef RENDERHELPERS
#define RENDERHELPERS

// System
#include <OpenGl.h>

// Qt
#include <QImage>
#include <QString>

// Assignment
#include <Euler.h>
#include <Vector.h>
#include <AffineMatrix.h>

namespace RenderHelpers
{
   double wrap(double min, double value, double max);
   double toDeg(double rad);
   double toRad(double deg);

   void glRotatee(const Euler rotation);
   void glRotateaa(double angle, Vector axis);

   void glTranslatev(const Vector translation);
   void glScalev(const Vector scale);
   void glVertexv(const Vector vertex);
   void glNormalv(const Vector normal);

   void glSphere(const Vector position, double scale);

   void glBillboard();

   AffineMatrix glGetMatrix(GLenum matrixMode);
   void glLoadMatrixa(AffineMatrix matrix);
   void glMultMatrixa(AffineMatrix matrix);
}

#endif
