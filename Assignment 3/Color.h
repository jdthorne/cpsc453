#ifndef COLOR_H
#define COLOR_H

// System

// Project

/**
 ******************************************************************************
 *
 *                   Color
 *
 ******************************************************************************
 */
class Color
{

public:
   Color(double r, double g, double b);
   virtual ~Color();

   int toQtRgb();

public:
   double r;
   double g;
   double b;
};

#endif
