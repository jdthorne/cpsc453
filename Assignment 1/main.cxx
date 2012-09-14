
#include <GLUT/glut.h>

void reshape(int width, int height)
{
   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   gluOrtho2D(0, width, 0, height);
} 

void display()
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

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(1280, 720);
   glutCreateWindow("CPSC453 Computer Graphics - Assignment 1");

   glutReshapeFunc(reshape);
   glutDisplayFunc(display);

   reshape(1280, 720);

   glutMainLoop();

   return 0;
}
