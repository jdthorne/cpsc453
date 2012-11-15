
// System

// Qt
#include <QImage>

// Project
#include <Color.h>

Color::Color(double r, double g, double b)
   : r(qBound(0.0, r, 1.0))
   , g(qBound(0.0, g, 1.0))
   , b(qBound(0.0, b, 1.0))
{
}

Color::~Color()
{
}

unsigned int Color::toQtRgb()
{
   return qRgb(qBound(0.0, r * 255.0, 255.0), 
               qBound(0.0, g * 255.0, 255.0), 
               qBound(0.0, b * 255.0, 255.0));
}

Color operator+(const Color& lhs, const Color& rhs)
{
   return Color( lhs.r + rhs.r,
                 lhs.g + rhs.g,
                 lhs.b + rhs.b );
}

Color& Color::operator+= (const Color& rhs)
{
   Color result = (*this + rhs);
   *this = result;

   return *this;
}

Color operator*(const Color& lhs, double value)
{
   return Color( lhs.r * value,
                 lhs.g * value,
                 lhs.b * value );
}
