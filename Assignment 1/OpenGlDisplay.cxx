
// System
#include <stdio.h>

// OpenGL
#include <GLUT/glut.h>

// Project
#include <OpenGlDisplay.h>

OpenGlDisplay::OpenGlDisplay()
   : mouseDown_(false)
   , originalImage_(std::string("landscape3.BMP"))
{
   originalImage_.quantizeTo(6);
   imageRenderer_.setImage(originalImage_);
}

OpenGlDisplay::~OpenGlDisplay()
{
}

void OpenGlDisplay::handleSizeChanged(int width, int height)
{
   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   gluOrtho2D(0, width, 0, height);

   width_ = width;
   height_ = height;

   imageRenderer_.setSize(width, height);
   controls_.handleSizeChanged(width, height);
}

void OpenGlDisplay::display()
{
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   glClear(GL_COLOR_BUFFER_BIT);

   imageRenderer_.render();
   controls_.render();

   glFlush();
   glutSwapBuffers();
}

int OpenGlDisplay::fixMouseY(int y)
{
   return height_ - y;
}

void OpenGlDisplay::handleMouseEvent(int button, int state, int x, int y)
{
   y = fixMouseY(y);

   controls_.handleMouseEvent(button, state, x, y);

   mouseDown_ = (button == GLUT_LEFT_BUTTON);
}

void OpenGlDisplay::handleMouseMotion(int x, int y)
{
   if (!mouseDown_)
   {
      return;
   }

   y = fixMouseY(y);

   controls_.handleMouseEvent(0, 0, x, y);   

   if (controls_.hasChanged())
   {
      originalImage_ = Image(std::string("landscape3.BMP"));
      originalImage_.quantizeTo(255 * controls_.sliderSetting());
      imageRenderer_.setImage(originalImage_);
   }
}

