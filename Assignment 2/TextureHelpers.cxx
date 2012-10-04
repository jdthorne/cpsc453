
// 3rdparty
#include <pcx.h>

// System

// Qt
#include <QGLWidget>

// Project
#include <TextureHelpers.h>

/**
 ******************************************************************************
 *
 *                   Load an image from a file, with support for PCX format
 *
 ******************************************************************************
 */
QImage TextureHelpers::loadImageFromFile(QString file)
{
   bool isPcxImage = (file.toLower().endsWith(".pcx"));

   if (!isPcxImage)
   {
      return QGLWidget::convertToGLFormat(QImage(file));
   }

   int width, height;
   unsigned char* pixels = NULL;

   LoadFilePCX(qPrintable(file), &pixels, &width, &height, false);   

   QImage pcxImage = QImage(pixels, width, height, QImage::Format_RGB32);

   return QGLWidget::convertToGLFormat(pcxImage);
}

/**
 ******************************************************************************
 *
 *                   Load a texture from a file, returning the texture id
 *
 ******************************************************************************
 */
GLuint TextureHelpers::loadTexture(QImage glImage)
{
   GLuint name = nextOpenGlTextureName();

   glBindTexture(GL_TEXTURE_2D, name);

   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   gluBuild2DMipmaps(GL_TEXTURE_2D, 4, glImage.width(), glImage.height(), 
                     GL_RGBA, GL_UNSIGNED_BYTE, glImage.bits());

   return name;
}

GLuint TextureHelpers::loadTextureFromFile(QString file)
{
   return loadTexture(loadImageFromFile(file));
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

GLuint TextureHelpers::nextOpenGlTextureName()
{
   if (!textureNamesWereGenerated)
   {
      glGenTextures(MAX_TEXTURES, textureNames);
      textureNamesWereGenerated = true;
   }

   static int nextIndex = 0;
   return textureNames[nextIndex++];
}

