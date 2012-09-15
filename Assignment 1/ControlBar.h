#ifndef CONTROLBAR_H
#define CONTROLBAR_H

// System
#include <string>

// Project
#include <PopupMenu.h>


class I_ControlBarHandler;

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
   ControlBar(I_ControlBarHandler& handler);
   virtual ~ControlBar();

public:
   void render();

   void handleSizeChanged(int width, int height);
   void handleMouseEvent(int x, int y, bool mouseDown);

   bool hasChanged();

public: // popup menu handler
   virtual void handleItemSelected(const PopupMenu* menu, int index, std::string item);

private: // helpers
   void renderBackground();
   void renderTitleText();
   void renderFileMenu();
   void renderOperationMenu();
   void renderSlider();

   double sliderSettingInRange(double min, double max);

   void handleSelectedOperationChanged();

private: // members
   I_ControlBarHandler& handler_;

   int width_;
   int height_;

   double sliderSetting_;

   bool fileMenuHovered_;
   bool operationMenuHovered_;
   bool sliderHovered_;

   std::string file_;

   PopupMenu fileMenu_;
   PopupMenu operationMenu_;

   int currentOperationIndex_;
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
   virtual void handleQuantilizeSelected(int levels) = 0;
   virtual void handleBrightenSelected(double setting) = 0;
   virtual void handleSaturateSelected(double scale) = 0;
   virtual void handleScaleSelected(double factor) = 0;
   virtual void handleRotateSelected(double angle) = 0;
   virtual void handleContrastSelected(double scale) = 0;
   virtual void handleBilinearScaleSelected(double factor) = 0;
   virtual void handleSwirlSelected(double angle) = 0;
   virtual void handleDissolveSelected(double mix) = 0;

};

#endif
