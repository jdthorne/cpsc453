
// System

// Project
#include <Color.h>
#include <MathHelpers.h>

const Color Color::BLACK = Color(0, 0, 0);

Color::Color(unsigned char r, unsigned char g, unsigned char b)
   : r(r)
   , g(g)
   , b(b)
{

}

Color::~Color()
{
}

Color Color::toLuminance()
{
   unsigned char lum = luminance(r, g, b);
   return Color(lum, lum, lum);
}

Color Color::blendedWith(Color rhs, double mix)
{
   unsigned char newR = blendColors(r, rhs.r, mix);
   unsigned char newG = blendColors(g, rhs.g, mix);
   unsigned char newB = blendColors(b, rhs.b, mix);

   return Color(newR, newG, newB);
}
