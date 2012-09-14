#ifndef IMAGERENDERER_H
#define IMAGERENDERER_H

// System

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
   void setImage(Image image);
   void setSize(int width, int height);

   void render();

private: // helpers
   void createOpenGlTexture();

private: // members
   Image image_;

   int width_;
   int height_;

};

#endif
