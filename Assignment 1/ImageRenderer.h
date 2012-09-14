#ifndef IMAGERENDERER_H
#define IMAGERENDERER_H

// System

// OpenGL
#include <GLUT/glut.h>

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
   void setOriginalImage(Image original);
   void setFilteredImage(Image filtered);
   void setSize(int width, int height);

   void render();

private: // helpers
   void createOpenGlTextures();
   void createTexture(int id, Image& image);

   void renderImage(int id, int x, int y, int width, int height);

private: // members
   Image originalImage_;
   Image filteredImage_;

   int width_;
   int height_;
   GLuint textureNames_[2];
};

#endif
