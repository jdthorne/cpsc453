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
class OpenGlDisplay : public I_ControlBarHandler
{

public:
   OpenGlDisplay();
   virtual ~OpenGlDisplay();

public:
   void handleSizeChanged(int width, int height);

   void handleMouseEvent(int button, int state, int x, int y);
   void handleMouseMotion(int x, int y);

   void reloadImageAndFilter();

   void display();

public: // I_ControlBarHandler
   virtual void handleQuantilizeSelected(int levels);
   virtual void handleBrightenSelected(double setting);
   virtual void handleSaturateSelected(double scale);
   virtual void handleScaleSelected(double factor);
   virtual void handleRotateSelected(double angle);
   virtual void handleContrastSelected(double scale);
   virtual void handleBilinearScaleSelected(double factor);
   virtual void handleSwirlSelected(double angle);

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
