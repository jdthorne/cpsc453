#ifndef IMAGE_H
#define IMAGE_H

// System
#include <string>

// Project
#include <RgbImage.h>

/**
 ******************************************************************************
 *
 *                    Image
 *
 ******************************************************************************
 */
class Image
{

public:
   Image();
   Image(std::string filename);
   Image(const Image& copy);
   ~Image();

   Image cloned();

public:
   int width();
   int height();

   int bytesPerRow();
   int bytesPerPixel();
   const void* data();

   void getPixel(int row, int column, unsigned char& r, unsigned char& g, unsigned char& b);
   void setPixel(int row, int column, unsigned char r, unsigned char g, unsigned char b);

   void quantizeTo(unsigned char levels);
   void brighten(double scale);

private: // helpers
   void createOpenGlTexture();

private: // members
   RgbImage* image_;
};

#endif
