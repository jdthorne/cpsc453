
// System
#include <cmath>
#include <sstream>
#include <stdio.h>

// OpenGl
#include <OpenGl.h>

// Project
#include <OpenGlHelpers.h>
#include <ControlBar.h>

const int BAR_HEIGHT = 25;

const int FILE_MENU_LEFT = 0;
const int FILE_MENU_TEXT = 20;
const int FILE_MENU_WIDTH = 180;

const int OPERATION_MENU_LEFT = FILE_MENU_LEFT + FILE_MENU_WIDTH;
const int OPERATION_MENU_WIDTH = 200;

const int SAVE_MENU_LEFT = OPERATION_MENU_LEFT + OPERATION_MENU_WIDTH;
const int SAVE_MENU_WIDTH = 100;

const int SLIDER_LEFT = SAVE_MENU_LEFT + SAVE_MENU_WIDTH;
const int SLIDER_TEXT = SLIDER_LEFT + 20;
const int SLIDER_BAR_START = SLIDER_TEXT + 60;
const int SLIDER_BAR_END_PADDING = 20;

const int TEXT_Y = 8;

ControlBar::ControlBar(I_ControlBarHandler& handler)
   : handler_(handler)
   , width_(0)
   , sliderSetting_(0.5)
   , fileMenu_(*this, "Image: landscape3.BMP", FILE_MENU_LEFT, 0, FILE_MENU_WIDTH, BAR_HEIGHT)
   , currentFileName_("landscape3.BMP")
   , operationMenu_(*this, "Operation: Quantilize", OPERATION_MENU_LEFT, 0, OPERATION_MENU_WIDTH, BAR_HEIGHT)
   , currentOperationIndex_(0)
   , currentOperationName_("Quantilize")
   , saveMenu_(*this, "Save As...", SAVE_MENU_LEFT, 0, SAVE_MENU_WIDTH, BAR_HEIGHT)
{

   // Setup the file menu
   fileMenu_.addItem("clouds1.BMP");
   fileMenu_.addItem("clouds2.BMP");
   fileMenu_.addItem("clouds3.BMP");
   fileMenu_.addItem("clouds4.BMP");
   fileMenu_.addItem("landscape1.bmp");
   fileMenu_.addItem("landscape2.BMP");
   fileMenu_.addItem("landscape3.BMP");

   // Setup the Operations menu
   operationMenu_.addItem("Quantilize");
   operationMenu_.addItem("Brighten");
   operationMenu_.addItem("Saturate");
   operationMenu_.addItem("Scale");
   operationMenu_.addItem("Rotate");
   operationMenu_.addItem("Contrast");
   operationMenu_.addItem("Bilinear Scale");
   operationMenu_.addItem("Swirl");
   operationMenu_.addItem("Dissolve");

   // Setup the save menu
   saveMenu_.addItem("Save Filtered Image...");
}

ControlBar::~ControlBar()
{
}

/**
 ******************************************************************************
 *
 *                   User Interface Drawing
 *
 ******************************************************************************
 */
void ControlBar::render()
{
   // Setup Alpha Blending, to make menus look better
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   // Render individual control bar components
   renderBackground();
   renderTitleText();

   fileMenu_.render();
   operationMenu_.render();
   saveMenu_.render();

   renderSlider();

   // Disable blending, so we don't screw up anything that happens next
   glDisable(GL_BLEND);
}

void ControlBar::renderBackground()
{
   // Render the backgrounds of the bars
   glColor4f(0, 0, 0, 0.85);
   drawRectangularQuad(0, 0, width_, BAR_HEIGHT);
   drawRectangularQuad(0, height_ - BAR_HEIGHT, width_, BAR_HEIGHT);

   // Render separator liens
   glColor4f(1, 1, 1, 1);
   drawLine(0, BAR_HEIGHT, width_, BAR_HEIGHT);
   drawLine(0, height_ - BAR_HEIGHT, width_, height_ - BAR_HEIGHT);
}

void ControlBar::renderTitleText()
{
   // Render the titlebar text in white
   glColor4f(1, 1, 1, 1);
   drawText(FILE_MENU_TEXT, height_ - BAR_HEIGHT + TEXT_Y, "CPSC453 Computer Graphics - Assignment 1 - James Thorne");
}

void ControlBar::renderSlider()
{
   // Render the slider separator & text
   glColor4f(1, 1, 1, 1);
   drawLine(SLIDER_LEFT, 0, SLIDER_LEFT, BAR_HEIGHT);
   drawText(SLIDER_TEXT, 8, "Amount:");

   // Render the slider "thumb"
   int sliderWidth = width_ - SLIDER_BAR_START - SLIDER_BAR_END_PADDING - 20;
   int sliderPosition = SLIDER_BAR_START + (sliderSetting_ * sliderWidth);
   drawRectangularQuad(sliderPosition, 0, 20, BAR_HEIGHT);

   // Render the "highlight" background if necessary
   if (sliderHovered_)
   {
      glColor4f(1, 1, 1, 0.2);
      drawRectangularQuad(SLIDER_BAR_START, 0, sliderWidth + 20, BAR_HEIGHT);
   }
}

/**
 ******************************************************************************
 *
 *                   Resizing
 *
 ******************************************************************************
 */
void ControlBar::handleSizeChanged(int width, int height)
{
   width_ = width;
   height_ = height;
}

/**
 ******************************************************************************
 *
 *                   Mouse Events
 *
 ******************************************************************************
 */
void ControlBar::handleMouseEvent(int x, int y, bool mouseDown)
{
   PopupMenu::deactivateMenus();
   fileMenu_.handleMouseEvent(x, y, mouseDown);
   operationMenu_.handleMouseEvent(x, y, mouseDown);
   saveMenu_.handleMouseEvent(x, y, mouseDown);

   // Determine if the slider should be highlighted
   sliderHovered_ = (y < BAR_HEIGHT) && (x > SLIDER_BAR_START && x < width_ - SLIDER_BAR_END_PADDING);

   // Move the slider if necessary
   if (sliderHovered_ && mouseDown)
   {
      handleSliderClicked(x);
   }

   // Redraw the UI, since it's probably changed
   glutPostRedisplay();
}

void ControlBar::handleSliderClicked(int x)
{
   // Figure out the new setting
   double sliderWidth = width_ - SLIDER_BAR_START - SLIDER_BAR_END_PADDING;
   sliderSetting_ = (x - SLIDER_BAR_START) / sliderWidth;

   // Make sure it's a valid setting
   if (sliderSetting_ < 0.0)
   {
      sliderSetting_ = 0;
   }
   if (sliderSetting_ > 1.0)
   {
      sliderSetting_ = 1.0;
   }

   // Handle the operation changing
   handleSelectedOperationChanged();
}

/**
 ******************************************************************************
 *
 *                   Popup Menu Events
 *
 ******************************************************************************
 */
void ControlBar::handleItemSelected(const PopupMenu* menu, int index, std::string item)
{
   if (menu == &fileMenu_)
   {
      handleFileMenuClicked(item);
   }

   if (menu == &operationMenu_)
   {
      handleOperationMenuClicked(item);
   }

   if (menu == &saveMenu_)
   {
      handleSaveMenuClicked();
   }

   handleSelectedOperationChanged();
}

void ControlBar::handleFileMenuClicked(std::string item)
{
   // Trigger the load event
   fileMenu_.setText("File: " + item);
   handler_.handleFileOpened(item);
}

void ControlBar::handleOperationMenuClicked(std::string item)
{
   // Set the operation
   currentOperationName_ = item;
   operationMenu_.setText("Operation: " + item);

   // Reset the slider
   sliderSetting_ = 0.25;
}

void ControlBar::handleSaveMenuClicked()
{
   // Determine the filename to save s
   std::ostringstream filename;
   filename << currentOperationName_ << "-";
   filename << sliderSetting_ << "-";
   filename << currentFileName_;

   // Trigger the save event
   handler_.handleFileSaved(filename.str());
}

/**
 ******************************************************************************
 *
 *                   Current Operation
 *
 ******************************************************************************
 */
void ControlBar::handleSelectedOperationChanged()
{
   // Notify the handler of the current selected operation
   if (currentOperationName_ == "Quantilize")
   {
      handler_.handleQuantilizeSelected(sliderSettingInRange(2, 255));
   }
   else if (currentOperationName_ == "Brighten")
   {
      handler_.handleBrightenSelected(sliderSettingInRange(0, 2));
   }
   else if (currentOperationName_ == "Saturate")
   {
      handler_.handleSaturateSelected(sliderSettingInRange(0, 2));
   }
   else if (currentOperationName_ == "Scale")
   {
      handler_.handleScaleSelected(sliderSettingInRange(0, 2));
   }
   else if (currentOperationName_ == "Rotate")
   {
      handler_.handleRotateSelected(sliderSettingInRange(0, 3.14159));
   }
   else if (currentOperationName_ == "Contrast")
   {
      handler_.handleContrastSelected(sliderSettingInRange(0, 2));
   }
   else if (currentOperationName_ == "Bilinear Scale")
   {
      handler_.handleBilinearScaleSelected(sliderSettingInRange(0, 2));
   }
   else if (currentOperationName_ == "Swirl")
   {
      handler_.handleSwirlSelected(sliderSettingInRange(0, 3.14159));
   }
   else if (currentOperationName_ == "Dissolve")
   {
      handler_.handleDissolveSelected(sliderSettingInRange(0, 1));
   }

   else
   {
      printf("[ControlBar] Error: Unknown operation selected: '%s'\n", currentOperationName_.data());
   }
}


/**
 ******************************************************************************
 *
 *                   Helpers
 *
 ******************************************************************************
 */
double ControlBar::sliderSettingInRange(double min, double max)
{
   // Return the slider setting with bounds, to make the above function easier
   double range = max - min;
   return min + (range * sliderSetting_);
}


