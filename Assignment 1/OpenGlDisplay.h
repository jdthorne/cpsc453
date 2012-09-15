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
   virtual void handleQuantilizeSelected(std::string file, int levels);
   virtual void handleBrightenSelected(std::string file, double setting);
   virtual void handleSaturateSelected(std::string file, double scale);
   virtual void handleScaleSelected(std::string file, double factor);
   virtual void handleRotateSelected(std::string file, double angle);
   virtual void handleContrastSelected(std::string file, double scale);
   virtual void handleBilinearScaleSelected(std::string file, double factor);
   virtual void handleSwirlSelected(std::string file, double angle);

private: // helpers
   int fixMouseY(int y);

private: // members
   bool mouseDown_;

   int width_;
   int height_;

   ImageRenderer imageRenderer_;

   ControlBar controls_;
};

#endif
