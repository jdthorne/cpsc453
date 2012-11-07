
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
   return qRgb(qBound(0.0, r * 255, 255.0), 
               qBound(0.0, g * 255, 255.0), 
               qBound(0.0, b * 255, 255.0));
}
