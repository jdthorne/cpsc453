#ifndef AFFINEMATRIX_H
#define AFFINEMATRIX_H

// System

// Project
#include <Vector.h>

class Euler;

/**
 ******************************************************************************
 *
 *                   AffineMatrix
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
   static AffineMatrix fromEuler(Euler euler);

   void loadToOpenGl();

private: // helpers

public: // members

   // Elements, stored in column-major order (i.e. [x][y])
   double element[4][4];
};

AffineMatrix operator*(const AffineMatrix& matrix, double scalar);
AffineMatrix operator*(const AffineMatrix& lhs, const AffineMatrix& rhs);

#endif
