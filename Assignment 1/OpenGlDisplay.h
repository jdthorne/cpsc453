#ifndef OPENGLDISPLAY_H
#define OPENGLDISPLAY_H

// System

// Project
#include <Image.h>
#include <ImageRenderer.h>
#include <ControlBar.h>

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
   void handleSizeChanged(int width, int height);

   void handleMouseEvent(int button, int state, int x, int y);
   void handleMouseMotion(int x, int y);

   void display();

private: // helpers
   int fixMouseY(int y);

private: // members
   bool mouseDown_;

   int width_;
   int height_;

   Image originalImage_;
   ImageRenderer imageRenderer_;

   ControlBar controls_;
};

#endif
