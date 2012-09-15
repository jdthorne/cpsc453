#ifndef MATHHELPERS_H
#define MATHHELPERS_H


/**
 ******************************************************************************
 *
 *                   Math Helpers
 *
 ******************************************************************************
 */
template <typename T>
inline T bound(T min, T value, T max)
{
   if (value <= min)
   {
      return min;
   };

   if (value >= max)
   {
      return max;
   }

   return value;
}

inline unsigned char blendColors(unsigned char a, unsigned char b, double mix)
{
   int newValue = (mix * a) + ( (1.0 - mix) * b );
   return bound<int>(0, newValue, 255);
}

inline unsigned char luminance(unsigned char r, unsigned char g, unsigned char b)
{
   return (0.3 * r) + (0.59 * g) + (0.11 * b);
}

#endif
