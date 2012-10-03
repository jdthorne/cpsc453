
// System
#include <OpenGl.h>

// Qt
#include <QGLWidget>

// Spacegame
#include <RenderHelpers.h>

double toDeg(double rad)
{
   return (rad * 180) / 3.1415926535;
}

/**
 ******************************************************************************
 *
 *                   Vector- and Quaternion- versions of standard functions
 *
 ******************************************************************************
 */
void RenderHelpers::glRotateq(const Quaternion quat)
{
   double angle = quat.angle();
   if (angle > 0.000001)
   {
      Vector axis = quat.axis();
      glRotatef(toDeg(angle), axis.x, axis.y, axis.z);
   }
}

void RenderHelpers::glVertexv(const Vector vertex)
{
   glVertex3f(vertex.x, vertex.y, vertex.z);
}

void RenderHelpers::glTranslatev(const Vector vertex)
{
   glTranslatef(vertex.x, vertex.y, vertex.z);
}

void RenderHelpers::glNormalv(const Vector vertex)
{
   glNormal3f(vertex.x, vertex.y, vertex.z);
}

/**
 ******************************************************************************
 *
 *                   Fancy Helpers
 *
 ******************************************************************************
 */
void RenderHelpers::glBillboard()
{
   float modelView[16];
   glGetFloatv(GL_MODELVIEW_MATRIX, modelView);

   for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++)
   {
      modelView[i*4 + j] = (i == j ? 1.0 : 0.0);
   }
   glLoadMatrixf(modelView);
}

void RenderHelpers::glSphere(const Vector position, double scale)
{
   glPushMatrix();

   glTranslatev(position);

   glBillboard();

   glScalef(scale, scale, scale);
   glBegin(GL_QUADS);

   glTexCoord2d(0.0, 0.0); glVertex2d(-1.0, -1.0);
   glTexCoord2d(1.0, 0.0); glVertex2d(1.0, -1.0);
   glTexCoord2d(1.0, 1.0); glVertex2d(1.0, 1.0);
   glTexCoord2d(0.0, 1.0); glVertex2d(-1.0, 1.0);

   glEnd();
   glPopMatrix();
}

/**
 ******************************************************************************
 *
 *                   Load a texture from a file, returning the texture id
 *
 ******************************************************************************
 */
GLuint RenderHelpers::loadTexture(QImage image)
{
   GLuint name = nextOpenGlTextureName();

   qDebug("Creating texture %d from %dx%d image", name, image.width(), image.height());

   QImage glImage = QGLWidget::convertToGLFormat(image);

   glBindTexture(GL_TEXTURE_2D, name);

   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   gluBuild2DMipmaps(GL_TEXTURE_2D, 4, glImage.width(), glImage.height(), 
                     GL_RGBA, GL_UNSIGNED_BYTE, glImage.bits());

   return name;
}

GLuint RenderHelpers::loadTextureFromFile(QString file, const char* format)
{
   return loadTexture(QImage(file, format));
}

/**
 ******************************************************************************
 *
 *                   Texture Management
 *
 ******************************************************************************
 */
const int MAX_TEXTURES = 8;
GLuint textureNames[MAX_TEXTURES];

bool textureNamesWereGenerated = false;

GLuint RenderHelpers::nextOpenGlTextureName()
{
   if (!textureNamesWereGenerated)
   {
      glGenTextures(MAX_TEXTURES, textureNames);
      textureNamesWereGenerated = true;
   }

   static int nextIndex = 0;
   return textureNames[nextIndex++];
}

