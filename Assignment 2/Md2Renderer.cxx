
// System
#include <OpenGl.h>

// Project
#include <Md5Renderer.h>

Md5Renderer::Md5Renderer()
{

}

Md5Renderer::~Md5Renderer()
{
}

void Md5Renderer::render()
{
   glBegin(GL_TRIANGLES);
   glVertex3f(0, 0, 0);
   glVertex3f(0, 1, 0);
   glVertex3f(1, 1, 0);
   glEnd();
}

