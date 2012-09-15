
// System
#include <cmath>
#include <sstream>

// OpenGl
#include <GLUT/glut.h>

// Project
#include <OpenGlHelpers.h>
#include <MathHelpers.h>
#include <ControlBar.h>

const int BAR_HEIGHT = 25;

const int FILE_MENU_LEFT = 0;
const int FILE_MENU_TEXT = 20;
const int FILE_MENU_RIGHT = 160;

const int OPERATION_MENU_LEFT = FILE_MENU_RIGHT;
const int OPERATION_MENU_TEXT = OPERATION_MENU_LEFT + 20;
const int OPERATION_MENU_RIGHT = OPERATION_MENU_LEFT + 200;

const int SLIDER_LEFT = OPERATION_MENU_RIGHT;
const int SLIDER_TEXT = SLIDER_LEFT + 20;
const int SLIDER_BAR_START = SLIDER_TEXT + 60;
const int SLIDER_BAR_END_PADDING = 20;

const int TEXT_Y = 8;

ControlBar::ControlBar(I_ControlBarHandler& handler)
   : handler_(handler)
   , width_(0)
   , sliderSetting_(0.5)
   , fileMenu_(*this, FILE_MENU_LEFT, BAR_HEIGHT + 1, FILE_MENU_RIGHT)
   , currentFileName_("landscape3.BMP")
   , currentFileText_("File: landscape3.BMP")
   , operationMenu_(*this, OPERATION_MENU_LEFT, BAR_HEIGHT + 1, SLIDER_LEFT - OPERATION_MENU_LEFT)
   , currentOperationIndex_(0)
   , currentOperationName_("Quantilize")
   , currentOperationText_("Operation: Quantilize")
{
   fileMenu_.addItem("Save Filtered Image");
   fileMenu_.addItem("clouds1.BMP");
   fileMenu_.addItem("clouds2.BMP");
   fileMenu_.addItem("clouds3.BMP");
   fileMenu_.addItem("clouds4.BMP");
   fileMenu_.addItem("landscape1.bmp");
   fileMenu_.addItem("landscape2.BMP");
   fileMenu_.addItem("landscape3.BMP");

   operationMenu_.addItem("Quantilize");
   operationMenu_.addItem("Brighten");
   operationMenu_.addItem("Saturate");
   operationMenu_.addItem("Scale");
   operationMenu_.addItem("Rotate");
   operationMenu_.addItem("Contrast");
   operationMenu_.addItem("Bilinear Scale");
   operationMenu_.addItem("Swirl");
   operationMenu_.addItem("Dissolve");
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
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   renderBackground();
   renderTitleText();
   renderFileMenu();
   renderOperationMenu();
   renderSlider();

   glDisable(GL_BLEND);
}

void ControlBar::renderBackground()
{
   glColor4f(0, 0, 0, 0.85);
   drawRectangularQuad(0, 0, width_, BAR_HEIGHT);
   drawRectangularQuad(0, height_ - BAR_HEIGHT, width_, BAR_HEIGHT);

   glColor4f(1, 1, 1, 1);
   drawLine(0, BAR_HEIGHT, width_, BAR_HEIGHT);
   drawLine(0, height_ - BAR_HEIGHT, width_, height_ - BAR_HEIGHT);
}

void ControlBar::renderTitleText()
{
   glColor4f(1, 1, 1, 1);
   drawText(FILE_MENU_TEXT, height_ - BAR_HEIGHT + TEXT_Y, "CPSC453 Computer Graphics - Assignment 1 - James Thorne");
}

void ControlBar::renderFileMenu()
{
   glColor4f(1, 1, 1, 1);
   drawText(FILE_MENU_TEXT, TEXT_Y, currentFileText_);

   if (fileMenuHovered_)
   {
      glColor4f(1, 1, 1, 0.2);
      drawRectangularQuad(FILE_MENU_LEFT, 0, OPERATION_MENU_LEFT, BAR_HEIGHT);
   }

   fileMenu_.render();
}

void ControlBar::renderOperationMenu()
{
   glColor4f(1, 1, 1, 1);
   drawLine(OPERATION_MENU_LEFT, 0, OPERATION_MENU_LEFT, BAR_HEIGHT);
   drawText(OPERATION_MENU_TEXT, TEXT_Y, currentOperationText_);

   if (operationMenuHovered_)
   {
      glColor4f(1, 1, 1, 0.2);
      drawRectangularQuad(OPERATION_MENU_LEFT, 0, SLIDER_LEFT - OPERATION_MENU_LEFT, BAR_HEIGHT);
   }

   operationMenu_.render();
}

void ControlBar::renderSlider()
{
   glColor4f(1, 1, 1, 1);
   drawLine(SLIDER_LEFT, 0, SLIDER_LEFT, BAR_HEIGHT);
   drawText(SLIDER_TEXT, 8, "Amount:");

   int sliderWidth = width_ - SLIDER_BAR_START - SLIDER_BAR_END_PADDING - 20;
   int sliderPosition = SLIDER_BAR_START + (sliderSetting_ * sliderWidth);
   drawRectangularQuad(sliderPosition, 0, 20, BAR_HEIGHT);

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
   fileMenu_.handleMouseEvent(x, y, mouseDown);
   operationMenu_.handleMouseEvent(x, y, mouseDown);

   fileMenuHovered_ = (y < BAR_HEIGHT) && (x > FILE_MENU_LEFT && x < FILE_MENU_RIGHT);
   operationMenuHovered_ = (y < BAR_HEIGHT) && (x > OPERATION_MENU_LEFT && x < SLIDER_LEFT);
   sliderHovered_ = (y < BAR_HEIGHT) && (x > SLIDER_BAR_START && x < width_ - SLIDER_BAR_END_PADDING);

   if (mouseDown)
   {
      if (sliderHovered_)
      {
         double sliderWidth = width_ - SLIDER_BAR_START - SLIDER_BAR_END_PADDING;
         sliderSetting_ = (x - SLIDER_BAR_START) / sliderWidth;

         if (sliderSetting_ < 0.0)
         {
            sliderSetting_ = 0;
         }
         if (sliderSetting_ > 1.0)
         {
            sliderSetting_ = 1.0;
         }

         handleSelectedOperationChanged();
      }

      fileMenu_.setVisible(fileMenuHovered_);
      operationMenu_.setVisible(operationMenuHovered_);
   }
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
      if (item == "Save Filtered Image")
      {
         std::ostringstream filename;
         filename << currentOperationName_ << "-";
         filename << sliderSetting_ << "-";
         filename << currentFileName_;
         handler_.handleFileSaved(filename.str());
      }
      else
      {
         currentFileText_ = "File: " + item;
         handler_.handleFileOpened(item);
      }
   }

   if (menu == &operationMenu_)
   {
      currentOperationName_ = item;
      currentOperationText_ = "Operation: " + item;
      sliderSetting_ = 0.5;

   }

   handleSelectedOperationChanged();
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
   if (currentOperationText_ == "Operation: Quantilize")
   {
      handler_.handleQuantilizeSelected(sliderSettingInRange(2, 255));
   }
   else if (currentOperationText_ == "Operation: Brighten")
   {
      handler_.handleBrightenSelected(sliderSettingInRange(0, 2));
   }
   else if (currentOperationText_ == "Operation: Saturate")
   {
      handler_.handleSaturateSelected(sliderSettingInRange(0, 2));
   }
   else if (currentOperationText_ == "Operation: Scale")
   {
      handler_.handleScaleSelected(sliderSettingInRange(0, 2));
   }
   else if (currentOperationText_ == "Operation: Rotate")
   {
      handler_.handleRotateSelected(sliderSettingInRange(0, 3.14159 / 2));
   }
   else if (currentOperationText_ == "Operation: Contrast")
   {
      handler_.handleContrastSelected(sliderSettingInRange(0, 2));
   }
   else if (currentOperationText_ == "Operation: Bilinear Scale")
   {
      handler_.handleBilinearScaleSelected(sliderSettingInRange(0, 2));
   }
   else if (currentOperationText_ == "Operation: Swirl")
   {
      handler_.handleSwirlSelected(sliderSettingInRange(0, 3.14159 / 2));
   }
   else if (currentOperationText_ == "Operation: Dissolve")
   {
      handler_.handleDissolveSelected(sliderSettingInRange(0, 1));
   }

   else
   {
      printf("[ControlBar] Error: Unknown operation selected: '%s'\n", currentOperationText_.data());
   }
}


/**
 ******************************************************************************
 *
 *                   Current Status
 *
 ******************************************************************************
 */
double ControlBar::sliderSettingInRange(double min, double max)
{
   double range = max - min;
   return min + (range * sliderSetting_);
}


