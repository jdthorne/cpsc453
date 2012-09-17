
// System
#include <stdio.h>

// OpenGL
#include <GLUT/glut.h>

// Project
#include <AssignmentCore.h>

AssignmentCore::AssignmentCore()
   : mouseDown_(false)
   , controls_(*this)
{
   // Use "Red Leaves" as the dissolve image
   dissolveImage_ = Image(std::string("images/RedLeavesTexture.bmp"));

   // Initialize the display
   handleFileOpened("landscape1.bmp");
   handleQuantilizeSelected(128);
}

AssignmentCore::~AssignmentCore()
{
}

/**
 ******************************************************************************
 *
 *                   Resizing
 *
 ******************************************************************************
 */
void AssignmentCore::handleSizeChanged(int width, int height)
{
   // Setup the OpenGL Viewport
   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   gluOrtho2D(0, width, 0, height);

   // Store the height
   width_ = width;
   height_ = height;

   // Delegate to children
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
void AssignmentCore::display()
{
   // Ensure we haven't screwed up the MODELVIEW matrix
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   // Clear the screen
   glClear(GL_COLOR_BUFFER_BIT);

   // Delegate rendering
   imageRenderer_.render();
   controls_.render();

   // Flush & Swap to the screen
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
void AssignmentCore::handleMouseEvent(int button, int state, int x, int y)
{
   // GLUT and OpenGL disagree about mouse coordinates :(
   y = fixMouseY(y);

   // Determine if mouse is down
   mouseDown_ = (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN);

   // Delegate to the control bar
   controls_.handleMouseEvent(x, y, mouseDown_);
}

void AssignmentCore::handleMouseMotion(int x, int y)
{
   // GLUT and OpenGL disagree about mouse coordinates :(
   y = fixMouseY(y);

   // Delegate to the control bar
   controls_.handleMouseEvent(x, y, mouseDown_);
}

int AssignmentCore::fixMouseY(int y)
{
   // GLUT and OpenGL disagree about mouse coordinates :(
   return height_ - y;
}

/**
 ******************************************************************************
 *
 *                   File Loading and Saving
 *
 ******************************************************************************
 */
void AssignmentCore::handleFileOpened(std::string file)
{
   // Delete the old image
   originalImage_.dispose();

   // Load the original image
   originalImage_ = Image("images/" + file);
   imageRenderer_.setOriginalImage(originalImage_);
}

void AssignmentCore::handleFileSaved(std::string file)
{
   // Save the filtered image
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
void AssignmentCore::handleQuantilizeSelected(int levels)
{
   setFilteredImage(originalImage_.quantized(levels));
}

void AssignmentCore::handleBrightenSelected(double setting)
{
   setFilteredImage(originalImage_.brightened(setting));
}

void AssignmentCore::handleSaturateSelected(double scale)
{
   setFilteredImage(originalImage_.saturated(scale));
}

void AssignmentCore::handleScaleSelected(double factor)
{
   setFilteredImage(originalImage_.scaled(factor));
}

void AssignmentCore::handleRotateSelected(double angle)
{
   setFilteredImage(originalImage_.rotated(angle));
}

void AssignmentCore::handleContrastSelected(double scale)
{
   setFilteredImage(originalImage_.contrasted(scale));
}

void AssignmentCore::handleBilinearScaleSelected(double factor)
{
   setFilteredImage(originalImage_.bilinearScaled(factor));
}

void AssignmentCore::handleSwirlSelected(double angle)
{
   setFilteredImage(originalImage_.swirled(angle));
}

void AssignmentCore::handleDissolveSelected(double mix)
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
void AssignmentCore::setFilteredImage(Image image)
{
   // Delete the old image
   filteredImage_.dispose();

   // Store the filtered image (so we can save it later if we want)
   filteredImage_ = image;

   // Give it to the renderer so it actually shows up
   imageRenderer_.setFilteredImage(image);
}

