#ifndef IMAGERENDERER_H
#define IMAGERENDERER_H

// System

// OpenGL
#include <OpenGl.h>

// Project
#include <Image.h>

/**
 ******************************************************************************
 *
 *                   ImageRenderer
 *
 ******************************************************************************
 */
class ImageRenderer
{

public:
   ImageRenderer();
   ~ImageRenderer();

public:
   void handleSizeChanged(int width, int height);

   void setOriginalImage(Image original);
   void setFilteredImage(Image filtered);

   void render();

private: // helpers
   void createOpenGlTextures();
   void createTexture(int id, Image& image);

   void renderImage(int id, int xCenter, int yCenter);

private: // members
   Image originalImage_;
   Image filteredImage_;

   int width_;
   int height_;

   GLuint textureNames_[2];
   int imageWidth_[2];
   int imageHeight_[2];
};

#endif
