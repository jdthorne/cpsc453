#ifndef AFFINEMATRIX_H
#define AFFINEMATRIX_H

// System

// Project
#include <Vector.h>

/**
 ******************************************************************************
 *
 *                   AffineMatrix
 *
 *  This class represents an affine transformation matrix; i.e. a 4-dimensional
 *  matrix containing translation, rotation, and scale.
 *
 *  To use the matrix, you can either access the elements directly (via
 *  matrix.element[col][row]), or use the various helper functions.
 *
 ******************************************************************************
 */
class AffineMatrix
{

public:
   AffineMatrix();
   virtual ~AffineMatrix();

   AffineMatrix operator=(const AffineMatrix& rhs);

public:
   static AffineMatrix identity();
   static AffineMatrix fromAxisAngle(Vector axis, double angle);
   static AffineMatrix fromTranslationVector(Vector translation);
   static AffineMatrix fromScaleVector(Vector scale);

   void loadToOpenGl();

private: // helpers

public: // members

   // Elements, stored in column-major order (i.e. [x][y])
   double element[4][4];
};

AffineMatrix operator*(const AffineMatrix& matrix, double scalar);
AffineMatrix operator*(const AffineMatrix& lhs, const AffineMatrix& rhs);

#define AFFINE_TO_GL(m) { m.element[0][0], m.element[0][1], m.element[0][2], m.element[0][3], \
                          m.element[1][0], m.element[1][1], m.element[1][2], m.element[1][3], \
                          m.element[2][0], m.element[2][1], m.element[2][2], m.element[2][3], \
                          m.element[3][0], m.element[3][1], m.element[3][2], m.element[3][3] }

#endif
