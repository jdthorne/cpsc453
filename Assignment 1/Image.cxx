
// System

// Project
#include <Image.h>
#include <RgbImage.h>

Image::Image()
   : imageData_(NULL)
{
}

Image::Image(std::string filename)
   : imageData_(NULL)
{
   loadFromFile(filename);
}

Image::~Image()
{
}

/**
 ******************************************************************************
 *
 * \brief            Use RgbImage to load from a bitmap file
 *
 ******************************************************************************
 */
void Image::loadFromFile(std::string filename)
{
   RgbImage imageLoader;
   imageLoader.LoadBmpFile(filename.data());

   int totalBytes = imageLoader.GetNumRows() * imageLoader.GetNumBytesPerRow();
   imageData_ = new char[totalBytes];
   memcpy(imageData_, imageLoader.ImageData(), totalBytes);
}
