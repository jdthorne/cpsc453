
// System
#include <cmath>

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
 *                   Copies
 *
 ******************************************************************************
 */
Image Image::blankCopy()
{
   // Make a blank image that's the same size
   Image result;
   result.image_ = new RgbImage(image_->GetNumRows(), image_->GetNumCols());

   return result;
}

Image Image::blankCopyOfSize(int width, int height)
{
   // Make a blank image that's a specific size
   Image result;
   result.image_ = new RgbImage(height, width);

   return result;
}

/**
 ******************************************************************************
 *
 *                   Saving
 *
 ******************************************************************************
 */
void Image::save(std::string filename)
{
   image_->WriteBmpFile(filename.data());
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
   // Return the color of the pixel at (x, y)
   unsigned char* base = image_->GetRgbPixel(y, x);

   return Color(base[0], base[1], base[2]);
}

void Image::setPixel(int x, int y, Color c)
{
   // Set the pixel at (x, y) to the color c
   unsigned char* base = image_->GetRgbPixel(y, x);
   base[0] = c.r;
   base[1] = c.g;
   base[2] = c.b;
}

/**
 ******************************************************************************
 *
 *                   Coordinate Verification
 *
 ******************************************************************************
 */
bool Image::coordsAreOk(int x, int y)
{
   // Ensure (x, y) is a valid point
   return (x >= 0 && x < width()) && (y >= 0 && y < height());
}

/**
 ******************************************************************************
 *
 *                   Misc Helper Functions
 *
 ******************************************************************************
 */
inline void rotateAroundCenter(int x, int y, int halfWidth, int halfHeight, double theta,
                               int& xOut, int& yOut)
{
   // Determine the (x, y) pair relative to the center
   int xRel = x - halfWidth;
   int yRel = y - halfHeight;

   // Rotate the pair by the angle theta
   int uRel = xRel * cos(theta) - yRel * sin(theta);
   int vRel = xRel * sin(theta) + yRel * cos(theta);

   // Return to (0, 0)-relative points
   xOut = uRel + halfWidth;
   yOut = vRel + halfHeight;
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

   // Create the quantization list
   char quantize[255];
   for (int i = 0; i < 256; i++)
   {
      quantize[i] = floor(255*floor(i*(levels-1)/255.0)/(levels-1));
   }

   // Quantize the individual pixels
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

   // Brighten individual pixels
   for (int y = 0; y < height(); y++)
   {
      for (int x = 0; x < width(); x++)
      {
         // Figure out current color
         Color color = getPixel(x, y);

         // Blend with black
         Color newColor = color.blendedWith(Color::BLACK, scaleFactor);

         // Save the color to the result
         result.setPixel(x, y, newColor);
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
         // Figure out the current color & luminence
         Color color = getPixel(x, y);
         Color luminance = color.toGreyscaleLuminanceColor();

         // Blend them together
         Color newColor = color.blendedWith(luminance, scale);

         // Save the color back
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
   Image result = this->blankCopyOfSize(width() * factor, height());

   for (int y = 0; y < result.height(); y++)
   {
      for (int x = 0; x < result.width(); x++)
      {
         // Determine the UV coordinates of the original pixel
         int u = x / factor;
         int v = y;

         // Save them back if they're OK
         if (coordsAreOk(u, v))
         {
            result.setPixel(x, y, getPixel(u, v));
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
   // Rotate CCW instead of CW
   theta *= -1;

   Image result = this->blankCopy();

   // Cache the center position
   int halfWidth = width() / 2;
   int halfHeight = height() / 2;

   for (int y = 0; y < height(); y++)
   {
      for (int x = 0; x < width(); x++)
      {
         // Determine rotated UV coordinates
         int u, v;
         rotateAroundCenter(x, y, halfWidth, halfHeight, theta, u, v);

         // Copy the pixel if the new UV is ok
         if (coordsAreOk(u, v))
         {
            result.setPixel(x, y, getPixel(u, v));
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
   int totalPixels = (height() * width());
   double averageLuminance = 0;
   for (int y = 0; y < height(); y++)
   {
      for (int x = 0; x < width(); x++)
      {
         Color color = getPixel(x, y);

         averageLuminance += ((double)color.luminance() / totalPixels);
      }
   }

   // Turn average luminance into a full color value
   Color luminanceColor = Color(averageLuminance, averageLuminance, averageLuminance);

   // Apply contrast to the pixels of the result
   for (int y = 0; y < height(); y++)
   {
      for (int x = 0; x < width(); x++)
      {
         // Get the original color
         Color color = getPixel(x, y);

         // Blend with average luminance
         Color newColor = color.blendedWith(luminanceColor, scale);

         // Return the result
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
Image Image::bilinearScaled(double factor)
{
   // Create an image with the new size
   Image result = this->blankCopyOfSize(width() * factor, height());

   // Copy the pixels via reverse-mapping
   for (int y = 0; y < result.height(); y++)
   {
      for (int x = 0; x < result.width(); x++)
      {
         // Determine the actual "u" value
         double u = x / factor;

         // Determine the "best" u-values
         int u1 = floor(u);
         int u2 = ceil(u);

         // We aren't scaling on y, so be lazy
         int v = y;

         // If all the coords are OK, do the filtering
         if (coordsAreOk(u1, v) && coordsAreOk(u2, v))
         {
            // Grab the two (u, v) pairs
            Color c1 = getPixel(u1, v);
            Color c2 = getPixel(u2, v);

            // Blend them together
            Color newColor = c1.blendedWith(c2, 0.5);

            // Save the pixel
            result.setPixel(x, y, newColor);
         }
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
Image Image::swirled(double theta)
{
   Image result = this->blankCopy();

   // Cache the center position
   int halfWidth = width() / 2;
   int halfHeight = height() / 2;

   // Swirl over the original image (i.e. forward-mapping)
   for (int v = 0; v < height(); v++)
   {
      for (int u = 0; u < width(); u++)
      {
         // Determine the pixel's distance from the center
         double uDistanceFromCenter = (u - halfWidth);
         double vDistanceFromCenter = (v - halfHeight);
         double distanceFromCenter = sqrt(   uDistanceFromCenter * uDistanceFromCenter 
                                           + vDistanceFromCenter * vDistanceFromCenter );

         // Determine the distance as a fraction
         double distanceFromCenterAsFraction = (distanceFromCenter / halfWidth);

         // Determine the position to write the pixel to
         int x, y;
         rotateAroundCenter(u, v, halfWidth, halfHeight, theta * distanceFromCenterAsFraction, x, y);

         // If the coords are OK, write them
         if (coordsAreOk(x, y) && coordsAreOk(u, v))
         {
            result.setPixel(x, y, getPixel(u, v));
         }
      }
   }

   return result;
}

/**
 ******************************************************************************
 *
 *                   Dissolve
 *
 ******************************************************************************
 */
Image Image::dissolved(double mix, Image& dissolveWith)
{
   Image result = dissolveWith.blankCopy();

   // Mix from original -> new
   mix = 1.0 - mix;

   // Mix each pixel
   for (int y = 0; y < result.height(); y++)
   {
      for (int x = 0; x < result.width(); x++)
      {
         // Check that the coords are OK on both images (they may be different sizes)
         if (coordsAreOk(x, y) && dissolveWith.coordsAreOk(x, y))
         {
            // Grab the two colors
            Color c1 = getPixel(x, y);
            Color c2 = dissolveWith.getPixel(x, y);

            // Blend them
            Color newColor = c1.blendedWith(c2, mix);

            // Write them to the result
            result.setPixel(x, y, newColor);
         }
      }
   }   

   return result;
}

