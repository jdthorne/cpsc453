
// System

// Project
#include <Image.h>
#include <RgbImage.h>

Image::Image()
{
}  

Image::Image(std::string filename)
   : image_(new RgbImage(filename.data()))
{
}

Image::Image(const Image& copy)
   : image_(copy.image_)
{
}

Image::~Image()
{
}

/**
 ******************************************************************************
 *
 *                   Accessors
 *
 ******************************************************************************
 */
int Image::width()
{
   return image_->GetNumCols();
}

int Image::height()
{
   return image_->GetNumRows();
}

int Image::bytesPerRow()
{
   return image_->GetNumBytesPerRow();
}

int Image::bytesPerPixel()
{
   // This class currently only supports RGB images
   return 3;
}

const void* Image::data()
{
   return image_->ImageData();
}

void Image::getPixel(int row, int column, unsigned char& r, unsigned char& g, unsigned char& b)
{
   unsigned char* base = image_->GetRgbPixel(row, column);
   r = base[0];
   g = base[1];
   b = base[2];
}

void Image::setPixel(int row, int column, unsigned char r, unsigned char g, unsigned char b)
{
   unsigned char* base = image_->GetRgbPixel(row, column);
   base[0] = r;
   base[1] = g;
   base[2] = b;
}

/**
 ******************************************************************************
 *
 *                   Image Transformations
 *
 ******************************************************************************
 */
void Image::quantizeTo(int levels)
{
   double quantize[255];
   for (int i = 0; i < 256; i++)
   {
      quantize[i] = 255 * ( (i * (levels - 1) / 255) ) / (levels - 1);
   }

   for (int row = 0; row < height(); row++)
   {
      for (int column = 0; column < width(); column++)
      {
         unsigned char r, g, b;
         getPixel(row, column, r, g, b);

         r = quantize[r];
         g = quantize[g];
         b = quantize[b];

         setPixel(row, column, r, g, b);
      }
   }
}

