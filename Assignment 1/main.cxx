
#include <OpenGl.h>
#include <AssignmentCore.h>

AssignmentCore* core = NULL;

/**
 ******************************************************************************
 *
 *                   GLUT Handler Functions
 *
 ******************************************************************************
 */
void reshape(int width, int height)
{
   // Delegate to the core
   core->handleSizeChanged(width, height);
} 

void mouseFunc(int button, int state, int x, int y)
{
   // Delegate to the core
   core->handleMouseEvent(button, state, x, y);
}

void motionFunc(int x, int y)
{
   // Delegate to the core
   core->handleMouseMotion(x, y);
}

void display()
{
   // Delegate to the core
   core->display();
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
   // Figure out the default window size
   int width = 800;
   int height = 400;

   // Init GLUT, set up a basic window
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(width, height);
   glutCreateWindow("CPSC453 Computer Graphics - Assignment 1");

   // Add our hook functions
   glutReshapeFunc(reshape);
   glutDisplayFunc(display);
   glutMouseFunc(mouseFunc);
   glutMotionFunc(motionFunc);
   glutPassiveMotionFunc(motionFunc);

   // Create our application core
   core = new AssignmentCore();
   core->handleSizeChanged(width, height);

   // Run the GLUT main loop
   glutMainLoop();

   return 0;
}
