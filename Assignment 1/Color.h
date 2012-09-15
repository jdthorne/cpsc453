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
   Color(unsigned char r, unsigned char g, unsigned char b);
   ~Color();

public:
   Color toLuminance();
   Color blendedWith(Color rhs, double mix);

   static const Color BLACK;

public: // members
   unsigned char r, g, b;
};

#endif
