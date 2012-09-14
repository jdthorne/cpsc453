
#include <GLUT/glut.h>
#include <OpenGlDisplay.h>

OpenGlDisplay openGlDisplay;

void reshape(int width, int height)
{
   openGlDisplay.reshape(width, height);
} 

void display()
{
   openGlDisplay.display();
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
