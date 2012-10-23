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

#endif
