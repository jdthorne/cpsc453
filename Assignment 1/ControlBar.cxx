
// System
#include <cmath>

// OpenGl
#include <GLUT/glut.h>

// Project
#include <OpenGlHelpers.h>
#include <MathHelpers.h>
#include <ControlBar.h>

const int FILE_MENU_TEXT = 20;

const int OPERATION_MENU_LEFT = 60;
const int OPERATION_MENU_TEXT = 80;

const int SLIDER_LEFT = 240;
const int SLIDER_TEXT = 260;
const int SLIDER_BAR_START = 320;
const int SLIDER_BAR_END_PADDING = 20;

const int TEXT_Y = 8;

ControlBar::ControlBar(I_ControlBarHandler& handler)
   : handler_(handler)
   , width_(0)
   , height_(25)
   , sliderSetting_(0.5)
   , file_("landscape3.BMP")
   , operationMenu_(*this, OPERATION_MENU_LEFT, height_ + 1, SLIDER_LEFT - OPERATION_MENU_LEFT)
   , currentOperationIndex_(0)
   , currentOperationText_("Operation: Quantilize")
{
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
   renderFileMenu();
   renderOperationMenu();
   renderSlider();

   glDisable(GL_BLEND);
}

void ControlBar::renderBackground()
{
   glColor4f(0, 0, 0, 0.85);
   drawRectangularQuad(0, 0, width_, height_);

   glColor4f(1, 1, 1, 1);
   drawLine(0, height_, width_, height_);
}

void ControlBar::renderFileMenu()
{
   glColor4f(1, 1, 1, 1);
   drawText(FILE_MENU_TEXT, TEXT_Y, "File");
}

void ControlBar::renderOperationMenu()
{
   glColor4f(1, 1, 1, 1);
   drawLine(OPERATION_MENU_LEFT, 0, OPERATION_MENU_LEFT, height_);
   drawText(OPERATION_MENU_TEXT, TEXT_Y, currentOperationText_);

   if (operationMenuHovered_)
   {
      glColor4f(1, 1, 1, 0.2);
      drawRectangularQuad(OPERATION_MENU_LEFT, 0, SLIDER_LEFT - OPERATION_MENU_LEFT, height_);
   }

   operationMenu_.render();
}

void ControlBar::renderSlider()
{
   glColor4f(1, 1, 1, 1);
   drawLine(SLIDER_LEFT, 0, SLIDER_LEFT, height_);
   drawText(SLIDER_TEXT, 8, "Amount:");

   int sliderWidth = width_ - SLIDER_BAR_START - SLIDER_BAR_END_PADDING - 20;
   int sliderPosition = SLIDER_BAR_START + (sliderSetting_ * sliderWidth);
   drawRectangularQuad(sliderPosition, 0, 20, height_);

   if (sliderHovered_)
   {
      glColor4f(1, 1, 1, 0.2);
      drawRectangularQuad(SLIDER_BAR_START, 0, sliderWidth + 20, height_);
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
   operationMenu_.handleMouseEvent(x, y, mouseDown);

   sliderHovered_ = (y < height_) && (x > SLIDER_BAR_START && x < width_ - SLIDER_BAR_END_PADDING);
   operationMenuHovered_ = (y < height_) && (x > OPERATION_MENU_LEFT && x < SLIDER_LEFT);

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

      if (operationMenuHovered_)
      {
         operationMenu_.show();
      }
      else
      {
         operationMenu_.hide();
      }
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
   currentOperationText_ = "Operation: " + item;
   sliderSetting_ = 0.5;

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


