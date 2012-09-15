
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
   Image baseImage(std::string("landscape3.BMP"));
   imageRenderer_.setOriginalImage(baseImage);

   handleQuantilizeSelected("landscape3.BMP", 0);
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
void OpenGlDisplay::handleQuantilizeSelected(std::string file, int levels)
{
   imageRenderer_.setFilteredImage(Image(file).quantize(levels));
}

void OpenGlDisplay::handleBrightenSelected(std::string file, double setting)
{
   imageRenderer_.setFilteredImage(Image(file).brighten(setting));
}

void OpenGlDisplay::handleSaturateSelected(std::string file, double scale)
{
   imageRenderer_.setFilteredImage(Image(file).saturate(scale));
}

void OpenGlDisplay::handleScaleSelected(std::string file, double factor)
{
   imageRenderer_.setFilteredImage(Image(file).scale(factor));
}

void OpenGlDisplay::handleRotateSelected(std::string file, double angle)
{
   imageRenderer_.setFilteredImage(Image(file).rotate(angle));
}

void OpenGlDisplay::handleContrastSelected(std::string file, double scale)
{
   imageRenderer_.setFilteredImage(Image(file).contrast(scale));
}

void OpenGlDisplay::handleBilinearScaleSelected(std::string file, double factor)
{
   imageRenderer_.setFilteredImage(Image(file).bilinearScale(factor));
}

void OpenGlDisplay::handleSwirlSelected(std::string file, double angle)
{
   imageRenderer_.setFilteredImage(Image(file).swirl(angle));
}

