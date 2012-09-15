
// System
#include <stdio.h>

// OpenGL
#include <GLUT/glut.h>

// Project
#include <OpenGlDisplay.h>

OpenGlDisplay::OpenGlDisplay()
   : mouseDown_(false)
{
   Image baseImage(std::string("landscape3.BMP"));
   imageRenderer_.setOriginalImage(baseImage);
   imageRenderer_.setFilteredImage(baseImage);
}

OpenGlDisplay::~OpenGlDisplay()
{
}

/**
 ******************************************************************************
 *
 *                   Resizing
 *
 ******************************************************************************
 */
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

/**
 ******************************************************************************
 *
 *                   Rendering
 *
 ******************************************************************************
 */
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

/**
 ******************************************************************************
 *
 *                   Mouse Events
 *
 ******************************************************************************
 */
void OpenGlDisplay::handleMouseEvent(int button, int state, int x, int y)
{
   y = fixMouseY(y);

   mouseDown_ = (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN);

   controls_.handleMouseEvent(x, y, mouseDown_);
}

void OpenGlDisplay::handleMouseMotion(int x, int y)
{
   y = fixMouseY(y);
   controls_.handleMouseEvent(x, y, mouseDown_);

   if (controls_.hasChanged())
   {  
      Image filteredImage(std::string("landscape3.BMP"));
      filteredImage.brighten(controls_.sliderSettingInRange(0, 2));

      imageRenderer_.setFilteredImage(filteredImage);
   }
}

int OpenGlDisplay::fixMouseY(int y)
{
   return height_ - y;
}
