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

   // Hand-written affine translation functions
   void jdRotateaa(double angle, Vector axis);
   void jdRotatea(const AffineMatrix rotation);
   void jdTranslatev(const Vector translation);
   void jdScalev(const Vector scale);
   void jdMultMatrixa(AffineMatrix matrix);

   void jdVertexv(const Vector vertex);
   void jdNormalv(const Vector normal);

   void jdLoadMatrixa(AffineMatrix matrix);

   void jdPushMatrix();
   void jdPopMatrix();
}

#endif
