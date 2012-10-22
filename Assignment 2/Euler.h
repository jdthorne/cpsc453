#ifndef EULER_H
#define EULER_H

// System

// Project
#include <AffineMatrix.h>

/**
 ******************************************************************************
 *
 *                   Euler
 *
 ******************************************************************************
 */
class Euler
{

public:
   Euler();
   Euler(double roll, double pitch, double yaw);
   virtual ~Euler();

public:
   static Euler fromAffineMatrix(AffineMatrix matrix);

public:
   double roll;
   double pitch;
   double yaw;

};

#endif
