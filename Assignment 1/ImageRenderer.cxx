
// System

// Project
#include <ImageRenderer.h>

ImageRenderer::ImageRenderer()
{
   glGenTextures(2, textureNames_);
}

ImageRenderer::~ImageRenderer()
{
}

/**
 ******************************************************************************
 *
 *                   Setup
 *
 ******************************************************************************
 */
void ImageRenderer::setOriginalImage(Image original)
{
   createTexture(0, original);
}

void ImageRenderer::setFilteredImage(Image filtered)
{
   createTexture(1, filtered);
}

void ImageRenderer::setSize(int width, int height)
{
   width_ = width;
   height_ = height;
}

/**
 ******************************************************************************
 *
 *                   Rendering
 *
 ******************************************************************************
 */
void ImageRenderer::createTexture(int id, Image& image)
{
   glBindTexture(GL_TEXTURE_2D, textureNames_[id]);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

   gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image.width(), image.height(),
                     GL_RGB, GL_UNSIGNED_BYTE, image.data() );
}

void ImageRenderer::render()
{
   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

   renderImage(0, 0, 0, width_ / 2, height_);
   renderImage(1, width_ / 2, 0, width_ / 2, height_);

   glDisable(GL_TEXTURE_2D);
}

void ImageRenderer::renderImage(int id, int x, int y, int width, int height)
{
   glBindTexture(GL_TEXTURE_2D, textureNames_[id]);

   glBegin(GL_QUADS);
   glColor4f(1, 1, 1, 1);

   glTexCoord2f(0, 0);
   glVertex3f(x, y, 0);

   glTexCoord2f(1, 0);
   glVertex3f(x + width, y, 0);

   glTexCoord2f(1, 1);
   glVertex3f(x + width, y + height, 0);

   glTexCoord2f(0, 1);
   glVertex3f(x, y + height, 0);

   glEnd();
}

