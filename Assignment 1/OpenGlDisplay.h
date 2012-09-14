#ifndef OPENGLDISPLAY_H
#define OPENGLDISPLAY_H

// System

// Project
#include <Image.h>
#include <ImageRenderer.h>

/**
 ******************************************************************************
 *
 *                   OpenGlDisplay
 *
 ******************************************************************************
 */
class OpenGlDisplay
{

public:
   OpenGlDisplay();
   ~OpenGlDisplay();

public:
   void reshape(int width, int height);
   void display();

private: // helpers

private: // members
   Image originalImage_;
   ImageRenderer imageRenderer_;

};

#endif
