#ifndef EULER_H
#define EULER_H

// System

// Project

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
   double roll;
   double pitch;
   double yaw;

};

#endif
