
// System

// OpenGl
#include <GLUT/glut.h>

// Project
#include <MathHelpers.h>
#include <ControlBar.h>

const int SLIDER_LEFT = 320;
const int SLIDER_RIGHT = 50;

ControlBar::ControlBar()
   : hasChanged_(false)
   , width_(0)
   , height_(50)
   , sliderSetting_(0)
{

}

ControlBar::~ControlBar()
{
}

void ControlBar::render()
{
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   glColor4f(0, 0, 0, 0.75);

   glBegin(GL_QUADS);
   glVertex3f(0, 0, 0);
   glVertex3f(width_, 0, 0);
   glVertex3f(width_, height_, 0);
   glVertex3f(0, height_, 0);
   glEnd();

   glColor4f(1, 1, 1, 1);
   drawText(20, 20, "File");
   drawText(80, 20, "Operation: Quantize");

   glColor4f(1, 0, 0, 1);
   int sliderWidth = width_ - SLIDER_LEFT - SLIDER_RIGHT;
   drawText(SLIDER_LEFT - 10, 20, "[");
   drawText(SLIDER_LEFT + (sliderSetting_ * sliderWidth), 20, "+");
   drawText(width_ - SLIDER_RIGHT + 20, 20, "]");

   glDisable(GL_BLEND);
}

void ControlBar::drawText(int x, int y, std::string text)
{
   glRasterPos2f(x, y);
   for (int i = 0; i < text.length(); i++)
   {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text.data()[i]);
   }
}

void ControlBar::handleSizeChanged(int width, int height)
{
   width_ = width;
}

void ControlBar::handleMouseEvent(int button, int state, int x, int y)
{
   if (y > height_)
   {
      return;
   }

   if (x > SLIDER_LEFT && x < width_ - SLIDER_RIGHT)
   {
      double sliderWidth = width_ - SLIDER_LEFT - SLIDER_RIGHT;
      sliderSetting_ = (x - SLIDER_LEFT) / sliderWidth;
      sliderSetting_ = bound(0, sliderSetting_, 1);
   }
   hasChanged_ = true;
}

bool ControlBar::hasChanged()
{
   bool result = hasChanged_;
   hasChanged_ = false;

   return result;
}

double ControlBar::sliderSetting()
{
   return sliderSetting_;
}

