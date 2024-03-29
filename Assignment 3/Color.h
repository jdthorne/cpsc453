#ifndef COLOR_H
#define COLOR_H

// System

// Project

/**
 ******************************************************************************
 *
 *                   Color class
 *
 * Represents an RGB color, consisting of R, G, and B values between 0.0 and 
 * 1.0.
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

   static Color mix(Color c1, Color c2, double mix);

public:
   double r;
   double g;
   double b;
};


Color operator*(const Color& lhs, double value);
Color operator*(const Color& lhs, const Color& rhs);
Color operator+(const Color& lhs, const Color& rhs);

#endif
