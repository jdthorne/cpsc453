
// System

// Qt
#include <QImage>

// Project
#include <Color.h>

Color::Color(double r, double g, double b)
   : r(r)
   , g(g)
   , b(b)
{

}

Color::~Color()
{
}

int Color::toQtRgb()
{
   return qRgb(qBound(0.1, r * 255, 254.0), 
               qBound(0.1, g * 255, 254.0), 
               qBound(0.1, b * 255, 254.0));
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
