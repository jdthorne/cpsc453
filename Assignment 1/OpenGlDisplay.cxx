
// System

// OpenGL
#include <GLUT/glut.h>

// Project
#include <OpenGlDisplay.h>

OpenGlDisplay::OpenGlDisplay()
{

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
}

void OpenGlDisplay::display()
{
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   glClear(GL_COLOR_BUFFER_BIT);

   glColor3f(1, 0, 0);

   glBegin(GL_TRIANGLES);
   glVertex3f(10, 0, 0);
   glVertex3f(0, 10, 0);
   glVertex3f(10, 10, 0);
   glEnd();

   glFlush();
   glutSwapBuffers();
}

