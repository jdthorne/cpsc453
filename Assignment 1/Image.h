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

   void getPixel(int x, int y, unsigned char& r, unsigned char& g, unsigned char& b);
   void setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b);

   bool coordsAreOk(int x, int y);

   Image& quantize(unsigned char levels);
   Image& brighten(double scale);
   Image& saturate(double scale);
   Image& scale(double factor);
   Image& rotate(double angle);
   Image& contrast(double scale);
   Image& bilinearScale(double factor);
   Image& swirl(double angle);

private: // helpers
   void createOpenGlTexture();

private: // members
   RgbImage* image_;
   std::string filename_;
};

#endif
