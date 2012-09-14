
// System

// OpenGL
#include <GLUT/glut.h>

// Project
#include <OpenGlDisplay.h>

OpenGlDisplay::OpenGlDisplay()
   : originalImage_(std::string("RedLeavesTexture.bmp"))
{
   originalImage_.quantizeTo(5);
   imageRenderer_.setImage(originalImage_);
}

OpenGlDisplay::~OpenGlDisplay()
{
}

void OpenGlDisplay::reshape(int width, int height)
{
   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   gluOrtho2D(0, width, 0, height);

   imageRenderer_.setSize(width, height);
}

void OpenGlDisplay::display()
{
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   glClear(GL_COLOR_BUFFER_BIT);

   imageRenderer_.render();

   glFlush();
   glutSwapBuffers();
}

