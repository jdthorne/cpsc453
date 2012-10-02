#ifndef RENDERHELPERS
#define RENDERHELPERS

// Qt
#include <QString>

// Spacegame
#include <Quaternion.h>
#include <Vector.h>

namespace RenderHelpers
{
   void glRotateq(const Quaternion quat);
   void glTranslatev(const Vector vertex);
   void glVertexv(const Vector vertex);
   void glNormalv(const Vector vertex);

   void glSphere(const Vector position, double scale);

   void glBillboard();
}

#endif
