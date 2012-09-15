
// System
#include <cmath>

// Project
#include <Image.h>
#include <RgbImage.h>
#include <MathHelpers.h>

Image::Image()
{
}  

Image::Image(std::string filename)
   : image_(new RgbImage(filename.data()))
   , filename_(filename)
{
}

Image::Image(const Image& copy)
   : image_(copy.image_)
   , filename_(copy.filename_)
{
}

Image::~Image()
{
}

Image Image::blankCopy()
{
   Image result;
   result.image_ = new RgbImage(image_->GetNumRows(), image_->GetNumCols());

   return result;
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
   // This class currently only supports RGB images; so this is always 3
   // If we supported RGBA in future, we'd need to make this more complicated.
   return 3;
}

const void* Image::data()
{
   return image_->ImageData();
}

/**
 ******************************************************************************
 *
 *                   Pixel Operations
 *
 ******************************************************************************
 */
Color Image::getPixel(int x, int y)
{
   unsigned char* base = image_->GetRgbPixel(y, x);

   return Color(base[0], base[1], base[2]);
}

void Image::setPixel(int x, int y, Color c)
{
   unsigned char* base = image_->GetRgbPixel(y, x);
   base[0] = c.r;
   base[1] = c.g;
   base[2] = c.b;
}

bool Image::coordsAreOk(int x, int y)
{
   return (x >= 0 && x < width()) && (y >= 0 && y < height());
}

/**
 ******************************************************************************
 *
 *                   Quantization
 *
 ******************************************************************************
 */
Image Image::quantized(unsigned char levels)
{
   Image result = this->blankCopy();

   // Create quantization list
   char quantize[255];
   for (int i = 0; i < 256; i++)
   {
      quantize[i] = floor(255*floor(i*(levels-1)/255.0)/(levels-1));
   }

   // Quantize individual pixels
   for (int y = 0; y < height(); y++)
   {
      for (int x = 0; x < width(); x++)
      {
         Color c = getPixel(x, y);

         c.r = quantize[c.r];
         c.g = quantize[c.g];
         c.b = quantize[c.b];

         result.setPixel(x, y, c);
      }
   }

   return result;
}

/**
 ******************************************************************************
 *
 *                   Brightness
 *
 ******************************************************************************
 */
Image Image::brightened(double scaleFactor)
{
   Image result = this->blankCopy();

   for (int y = 0; y < height(); y++)
   {
      for (int x = 0; x < width(); x++)
      {
         Color c = getPixel(x, y);

         c.r = bound<int>(0, c.r * scaleFactor, 255);
         c.g = bound<int>(0, c.g * scaleFactor, 255);
         c.b = bound<int>(0, c.b * scaleFactor, 255);

         result.setPixel(x, y, c);
      }
   }     

   return result;
}

/**
 ******************************************************************************
 *
 *                   Saturation
 *
 ******************************************************************************
 */
Image Image::saturated(double scale)
{
   Image result = this->blankCopy();

   for (int y = 0; y < height(); y++)
   {
      for (int x = 0; x < width(); x++)
      {
         Color color = getPixel(x, y);
         Color luminance = color.toLuminance();

         Color newColor = color.blendedWith(luminance, scale);

         result.setPixel(x, y, newColor);
      }
   }

   return result;
}


/**
 ******************************************************************************
 *
 *                   Scale
 *
 ******************************************************************************
 */
Image Image::scaled(double factor)
{
   Image result = this->blankCopy();

   for (int y = 0; y < height(); y++)
   {
      for (int x = 0; x < width(); x++)
      {
         int u = x / factor;
         int v = y;

         if (coordsAreOk(u, v))
         {
            result.setPixel(x, y, getPixel(u, v));
         }
         else
         {  
            result.setPixel(x, y, Color::BLACK);
         }
      }
   }     

   return result;
}


/**
 ******************************************************************************
 *
 *                   Rotate
 *
 ******************************************************************************
 */
Image Image::rotated(double theta)
{
   theta *= -1;

   Image result = this->blankCopy();

   int halfWidth = width() / 2;
   int halfHeight = height() / 2;

   for (int y = 0; y < height(); y++)
   {
      for (int x = 0; x < width(); x++)
      {
         int xRel = x - halfWidth;
         int yRel = y - halfHeight;

         int uRel = xRel * cos(theta) - yRel * sin(theta);
         int vRel = xRel * sin(theta) + yRel * cos(theta);

         int u = uRel + halfWidth;
         int v = vRel + halfHeight;

         if (coordsAreOk(u, v))
         {
            result.setPixel(x, y, getPixel(u, v));
         }
         else
         {
            result.setPixel(x, y, Color::BLACK);
         }
      }
   }

   return result;
}


/**
 ******************************************************************************
 *
 *                   Contrast
 *
 ******************************************************************************
 */
Image Image::contrasted(double scale)
{
   Image result = this->blankCopy();

   // Calculate average luminance
   int totalOfRowLuminances = 0;
   for (int y = 0; y < height(); y++)
   {
      int totalLuminanceOfRow = 0;
      for (int x = 0; x < width(); x++)
      {
         Color color = getPixel(x, y);

         totalLuminanceOfRow += luminance(color.r, color.g, color.b);
      }

      int actualLuminanceOfRow = (totalLuminanceOfRow / width());
      totalOfRowLuminances += actualLuminanceOfRow;
   }

   int averageLuminance = (totalOfRowLuminances / height());

   Color luminanceColor = Color(averageLuminance, averageLuminance, averageLuminance);

   // Apply contrast
   for (int y = 0; y < height(); y++)
   {
      for (int x = 0; x < width(); x++)
      {
         Color color = getPixel(x, y);

         Color newColor = color.blendedWith(luminanceColor, scale);
         result.setPixel(x, y, newColor);
      }
   }     

   return result;
}


/**
 ******************************************************************************
 *
 *                   Bilinear Scaling
 *
 ******************************************************************************
 */
Image Image::bilinearScaled(double scale)
{
   Image result = this->blankCopy();

   for (int y = 0; y < height(); y++)
   {
      for (int x = 0; x < width(); x++)
      {

      }
   }   

   return result;
}


/**
 ******************************************************************************
 *
 *                   Swirl
 *
 ******************************************************************************
 */
Image Image::swirled(double angle)
{
   printf("Warning: [Image] 'swirl()' is not implemented\n");

   return *this;
}


