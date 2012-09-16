
// System

// Project
#include <ImageRenderer.h>

ImageRenderer::ImageRenderer()
{
   // Generate the texture names - this seems to be slow, so only do it on
   // construction.
   glGenTextures(2, textureNames_);
}

ImageRenderer::~ImageRenderer()
{
}

/**
 ******************************************************************************
 *
 *                   Setting images
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

/**
 ******************************************************************************
 *
 *                   Resizing
 *
 ******************************************************************************
 */
void ImageRenderer::handleSizeChanged(int width, int height)
{
   width_ = width;
   height_ = height;
}

/**
 ******************************************************************************
 *
 *                   Creating textures in OpenGL
 *
 ******************************************************************************
 */
void ImageRenderer::createTexture(int id, Image& image)
{
   // Remember the size so we can center the image later
   imageWidth_[id] = image.width();
   imageHeight_[id] = image.height();

   // Tell OpenGL which texture we want
   glBindTexture(GL_TEXTURE_2D, textureNames_[id]);

   // Tell OpenGL how to handle the texture (repeat on edges, use
   // nearest-neighbour interpolation)
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

   // Set the magnification and minification filters to nearest-neighbour
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

   // Actually push the texture to OpenGL (yay GLUT making it easy!)
   gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image.width(), image.height(),
                     GL_RGB, GL_UNSIGNED_BYTE, image.data() );
}

/**
 ******************************************************************************
 *
 *                   Render the actual images
 *
 ******************************************************************************
 */
void ImageRenderer::render()
{
   // Tell OpenGL we're using textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

   // Render the two images at x = 1/4 and x = 3/4
   renderImage(0, width_ * 0.25, height_ * 0.5);
   renderImage(1, width_ * 0.75, height_ * 0.5);

   // Turn textures off so we don't screw up anything that happens next
   glDisable(GL_TEXTURE_2D);
}

void ImageRenderer::renderImage(int id, int xCenter, int yCenter)
{
   // Figure out the offsets from the center
   int dx = imageWidth_[id];
   int dy = imageHeight_[id];

   // Tell OpenGL which texture we want
   glBindTexture(GL_TEXTURE_2D, textureNames_[id]);

   // Tell OpenGL we're drawing quads, and in white (so it doesn't tint our display)
   glBegin(GL_QUADS);
   glColor4f(1, 1, 1, 1);

   // Give OpenGL the four coordinates
   glTexCoord2f(0, 0);
   glVertex3f(xCenter - dx, yCenter - dy, 0);

   glTexCoord2f(1, 0);
   glVertex3f(xCenter + dx, yCenter - dy, 0);

   glTexCoord2f(1, 1);
   glVertex3f(xCenter + dx, yCenter + dy, 0);

   glTexCoord2f(0, 1);
   glVertex3f(xCenter - dx, yCenter + dy, 0);

   // Tell OpenGL we're done
   glEnd();
}

