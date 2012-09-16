
// System

// OpenGl
#include <GLUT/glut.h>

// Project
#include <OpenGlHelpers.h>

void drawRectangularQuad(int x, int y, int width, int height)
{
   // Draw a simple rectangle
   glBegin(GL_QUADS);
   glVertex3f(x, y, 0);
   glVertex3f(x + width, y, 0);
   glVertex3f(x + width, y + height, 0);
   glVertex3f(x, y + height, 0);
   glEnd(); 
}

void drawLine(int x1, int y1, int x2, int y2)
{
   // Draw a simple line
   glBegin(GL_LINES);
   glVertex3f(x1, y1, 0);
   glVertex3f(x2, y2, 0);
   glEnd();
}

void drawText(int x, int y, std::string text)
{
   // Draw text using GLUT (yay GLUT for making things easy!)
   glRasterPos2f(x, y);
   for (int i = 0; i < text.length(); i++)
   {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text.data()[i]);
   }
}
