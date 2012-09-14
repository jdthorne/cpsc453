#ifndef OPENGLDISPLAY_H
#define OPENGLDISPLAY_H

// System

// Project
#include <Image.h>

/**
 ******************************************************************************
 *
 * \brief            OpenGlDisplay
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
   Image currentImage;

};

#endif
