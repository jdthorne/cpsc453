
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

/**
 ******************************************************************************
 *
 *                   Helper Functions
 *
 ******************************************************************************
 */
inline unsigned char blendColorValues(unsigned char a, unsigned char b, double mix)
{
   int newValue = (mix * a) + ( (1.0 - mix) * b );
   
   if (newValue < 0)
   {
      return 0;
   }
   if (newValue > 255)
   {
      return 255;
   }

   return newValue;
}

/**
 ******************************************************************************
 *
 *                   Color Operations
 *
 ******************************************************************************
 */
unsigned char Color::luminance()
{
   return (0.3 * r) + (0.59 * g) + (0.11 * b);
}

Color Color::toLuminance()
{
   return Color(luminance(), luminance(), luminance());
}

Color Color::blendedWith(Color rhs, double mix)
{
   unsigned char newR = blendColorValues(r, rhs.r, mix);
   unsigned char newG = blendColorValues(g, rhs.g, mix);
   unsigned char newB = blendColorValues(b, rhs.b, mix);

   return Color(newR, newG, newB);
}
