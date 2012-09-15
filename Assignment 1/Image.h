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

   Image blankCopy();

public:
   int width();
   int height();

   int bytesPerRow();
   int bytesPerPixel();
   const void* data();

   void getPixel(int x, int y, unsigned char& r, unsigned char& g, unsigned char& b);
   void setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b);

   bool coordsAreOk(int x, int y);

   Image quantized(unsigned char levels);
   Image brightened(double scale);
   Image saturated(double scale);
   Image scaled(double factor);
   Image rotated(double angle);
   Image contrasted(double scale);
   Image bilinearScaled(double factor);
   Image swirled(double angle);

private: // helpers
   void createOpenGlTexture();

private: // members
   RgbImage* image_;
   std::string filename_;
};

#endif
