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

   unsigned int toQtRgb();
   Color& operator+= (const Color& rhs);

public:
   double r;
   double g;
   double b;
};

Color operator*(const Color& lhs, double value);
Color operator+(const Color& lhs, const Color& rhs);

#endif
