#ifndef CONTROLBAR_H
#define CONTROLBAR_H

// System
#include <string>

// Project
#include <PopupMenu.h>

/**
 ******************************************************************************
 *
 *                   ControlBar
 *
 ******************************************************************************
 */
class ControlBar : public I_PopupMenuHandler
{

public:
   ControlBar();
   virtual ~ControlBar();

public:
   void render();

   void handleSizeChanged(int width, int height);
   void handleMouseEvent(int x, int y, bool mouseDown);

   bool hasChanged();
   double sliderSettingInRange(double min, double max);

public: // popup menu handler
   virtual void handleItemSelected(const PopupMenu* menu, int index, std::string item);

private: // helpers
   void renderBackground();
   void renderFileMenu();
   void renderOperationMenu();
   void renderSlider();

private: // members
   bool hasChanged_;

   int width_;
   int height_;

   double sliderSetting_;

   bool fileMenuHovered_;
   bool operationMenuHovered_;
   bool sliderHovered_;

   PopupMenu operationMenu_;

   std::string currentOperationText_;
};

/**
 ******************************************************************************
 *
 *                   Interface for handling Control Bar changes
 *
 ******************************************************************************
 */
class I_ControlBarHandler
{
public:
   virtual ~I_ControlBarHandler() {};

public:
   virtual void handleOperationChanged() = 0;

};

#endif
