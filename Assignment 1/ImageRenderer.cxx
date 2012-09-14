
// System

// OpenGL
#include <GLUT/glut.h>

// Project
#include <ImageRenderer.h>

ImageRenderer::ImageRenderer()
   : image_()
{

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
void ImageRenderer::setImage(Image image)
{
   image_ = image;
   createOpenGlTexture();
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
void ImageRenderer::createOpenGlTexture()
{
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

   gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image_.width(), image_.height(),
                     GL_RGB, GL_UNSIGNED_BYTE, image_.data() );
}

void ImageRenderer::render()
{
   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

   glBegin(GL_QUADS);

   glTexCoord2f(0, 0);
   glVertex3f(0, 0, 0);

   glTexCoord2f(1, 0);
   glVertex3f(width_, 0, 0);

   glTexCoord2f(1, 1);
   glVertex3f(width_, height_, 0);

   glTexCoord2f(0, 1);
   glVertex3f(0, height_, 0);

   glEnd();
   glDisable(GL_TEXTURE_2D);
}
