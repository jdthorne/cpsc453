#ifndef CONTROLBAR_H
#define CONTROLBAR_H

// System
#include <string>

// Project

/**
 ******************************************************************************
 *
 *                   ControlBar
 *
 ******************************************************************************
 */
class ControlBar
{

public:
   ControlBar();
   ~ControlBar();

public:

   void render();

   void handleSizeChanged(int width, int height);
   void handleMouseEvent(int button, int state, int x, int y);

   bool hasChanged();
   double sliderSetting();

private: // helpers
   void drawText(int x, int y, std::string text);

private: // members
   bool hasChanged_;

   int width_;
   int height_;

   double sliderSetting_;
};

#endif
