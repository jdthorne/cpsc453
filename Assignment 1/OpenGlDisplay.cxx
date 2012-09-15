
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
   dissolveImage_ = Image(std::string("images/RedLeavesTexture.bmp"));

   handleFileOpened("landscape1.bmp");
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

   controls_.handleSizeChanged(width, height);
   imageRenderer_.handleSizeChanged(width, height);
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
 *                   File Loading and Saving
 *
 ******************************************************************************
 */
void OpenGlDisplay::handleFileOpened(std::string file)
{
   originalImage_ = Image("images/" + file);
   imageRenderer_.setOriginalImage(originalImage_);
}

void OpenGlDisplay::handleFileSaved(std::string file)
{
   std::string path = "images/" + file;

   filteredImage_.save(path);
}


/**
 ******************************************************************************
 *
 *                   Image Operations
 *
 ******************************************************************************
 */
void OpenGlDisplay::handleQuantilizeSelected(int levels)
{
   setFilteredImage(originalImage_.quantized(levels));
}

void OpenGlDisplay::handleBrightenSelected(double setting)
{
   setFilteredImage(originalImage_.brightened(setting));
}

void OpenGlDisplay::handleSaturateSelected(double scale)
{
   setFilteredImage(originalImage_.saturated(scale));
}

void OpenGlDisplay::handleScaleSelected(double factor)
{
   setFilteredImage(originalImage_.scaled(factor));
}

void OpenGlDisplay::handleRotateSelected(double angle)
{
   setFilteredImage(originalImage_.rotated(angle));
}

void OpenGlDisplay::handleContrastSelected(double scale)
{
   setFilteredImage(originalImage_.contrasted(scale));
}

void OpenGlDisplay::handleBilinearScaleSelected(double factor)
{
   setFilteredImage(originalImage_.bilinearScaled(factor));
}

void OpenGlDisplay::handleSwirlSelected(double angle)
{
   setFilteredImage(originalImage_.swirled(angle));
}

void OpenGlDisplay::handleDissolveSelected(double mix)
{
   setFilteredImage(originalImage_.dissolved(mix, dissolveImage_));
}

/**
 ******************************************************************************
 *
 *                   Image Handling
 *
 ******************************************************************************
 */
void OpenGlDisplay::setFilteredImage(Image image)
{
   filteredImage_ = image;
   imageRenderer_.setFilteredImage(image);
}

