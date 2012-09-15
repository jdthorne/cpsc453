
// System
#include <stdio.h>

// OpenGL
#include <GLUT/glut.h>

// Project
#include <OpenGlDisplay.h>

OpenGlDisplay::OpenGlDisplay()
   : mouseDown_(false)
   , controls_(*this)
{
   originalImage_ = Image(std::string("images/landscape3.BMP"));
   dissolveImage_ = Image(std::string("images/RedLeavesTexture.bmp"));
   imageRenderer_.setOriginalImage(originalImage_);

   handleQuantilizeSelected(128);
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
}

int OpenGlDisplay::fixMouseY(int y)
{
   return height_ - y;
}

/**
 ******************************************************************************
 *
 *                   Control Bar
 *
 ******************************************************************************
 */
void OpenGlDisplay::handleQuantilizeSelected(int levels)
{
   imageRenderer_.setFilteredImage(originalImage_.quantized(levels));
}

void OpenGlDisplay::handleBrightenSelected(double setting)
{
   imageRenderer_.setFilteredImage(originalImage_.brightened(setting));
}

void OpenGlDisplay::handleSaturateSelected(double scale)
{
   imageRenderer_.setFilteredImage(originalImage_.saturated(scale));
}

void OpenGlDisplay::handleScaleSelected(double factor)
{
   imageRenderer_.setFilteredImage(originalImage_.scaled(factor));
}

void OpenGlDisplay::handleRotateSelected(double angle)
{
   imageRenderer_.setFilteredImage(originalImage_.rotated(angle));
}

void OpenGlDisplay::handleContrastSelected(double scale)
{
   imageRenderer_.setFilteredImage(originalImage_.contrasted(scale));
}

void OpenGlDisplay::handleBilinearScaleSelected(double factor)
{
   imageRenderer_.setFilteredImage(originalImage_.bilinearScaled(factor));
}

void OpenGlDisplay::handleSwirlSelected(double angle)
{
   imageRenderer_.setFilteredImage(originalImage_.swirled(angle));
}

void OpenGlDisplay::handleDissolveSelected(double mix)
{
   imageRenderer_.setFilteredImage(originalImage_.dissolved(mix, dissolveImage_));
}

