
#include <GLUT/glut.h>
#include <OpenGlDisplay.h>

OpenGlDisplay* openGlDisplay = NULL;

/**
 ******************************************************************************
 *
 *                   GLUT Handle Functions
 *
 ******************************************************************************
 */
void reshape(int width, int height)
{
   openGlDisplay->handleSizeChanged(width, height);
} 

void mouseFunc(int button, int state, int x, int y)
{
   openGlDisplay->handleMouseEvent(button, state, x, y);
}

void motionFunc(int x, int y)
{
   openGlDisplay->handleMouseMotion(x, y);
}

void display()
{
   openGlDisplay->display();
}

void idle()
{
   glutPostRedisplay();
}

/**
 ******************************************************************************
 *
 *                   Main Initialization
 *
 ******************************************************************************
 */
int main(int argc, char** argv)
{
   int width = 1150;
   int height = 450;

   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(width, height);
   glutCreateWindow("CPSC453 Computer Graphics - Assignment 1");

   glutReshapeFunc(reshape);
   glutDisplayFunc(display);
   glutMouseFunc(mouseFunc);
   glutMotionFunc(motionFunc);
   glutPassiveMotionFunc(motionFunc);
   glutIdleFunc(idle);

   openGlDisplay = new OpenGlDisplay();

   reshape(width, height);

   glutMainLoop();

   return 0;
}
