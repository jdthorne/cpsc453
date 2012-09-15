#ifndef IMAGE_H
#define IMAGE_H

// System
#include <string>

// Project
#include <RgbImage.h>
#include <Color.h>

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

   Color getPixel(int x, int y);
   void setPixel(int x, int y, Color c);

   bool coordsAreOk(int x, int y);

   void save(std::string filename);

   Image quantized(unsigned char levels);
   Image brightened(double scale);
   Image saturated(double scale);
   Image scaled(double factor);
   Image rotated(double angle);
   Image contrasted(double scale);
   Image bilinearScaled(double factor);
   Image swirled(double angle);
   Image dissolved(double mix, Image& image);

private: // helpers
   void createOpenGlTexture();

private: // members
   RgbImage* image_;
   std::string filename_;
};

#endif
