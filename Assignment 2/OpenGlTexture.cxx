
// System

// Qt
#include <QImage>
#include <QGLWidget>

// Project
#include <pcx.h>
#include <OpenGlTexture.h>

QList<GlTextureName> OpenGlTexture::availableTextureNames_;

OpenGlTexture::OpenGlTexture(QString filename)
{
   ensureOpenGlTexturesAreInitialized();
   loadFromFile(filename);
}

OpenGlTexture::~OpenGlTexture()
{
   availableTextureNames_.append(textureName_);
}

/**
 ******************************************************************************
 *
 *                   Accessors
 *
 ******************************************************************************
 */
double OpenGlTexture::width()
{
   return width_;
}

double OpenGlTexture::height()
{
   return height_;
}

/**
 ******************************************************************************
 *
 *                   Binding (i.e. the useful part)
 *
 ******************************************************************************
 */
void OpenGlTexture::bind()
{
   glBindTexture(GL_TEXTURE_2D, textureName_);
}

/**
 ******************************************************************************
 *
 *                   Initialization
 *
 ******************************************************************************
 */
void OpenGlTexture::ensureOpenGlTexturesAreInitialized()
{
   static bool texturesAreInitialized = false;
   if (texturesAreInitialized)
   {
      return;
   }

   const int maxTextures = 16;
   GlTextureName names[maxTextures];

   glGenTextures(maxTextures, names);
   for (int i = 0; i < maxTextures; i++)
   {
      availableTextureNames_.append(names[i]);
   }

   texturesAreInitialized = true;
}

/**
 ******************************************************************************
 *
 *                   Texture Loading
 *
 ******************************************************************************
 */
void OpenGlTexture::loadFromFile(QString filename)
{
   bool isPcxTexture = (filename.toLower().endsWith(".pcx"));
   if (isPcxTexture)
   {
      loadFromPcx(filename);
   }
   else
   {
      loadFromQImage(filename);
   }
}

void OpenGlTexture::loadFromPcx(QString file)
{
   int width, height;
   unsigned char* pixels = NULL;

   LoadFilePCX(qPrintable(file), &pixels, &width, &height, true);   
   loadFromBinary(pixels, width, height);
}

void OpenGlTexture::loadFromQImage(QString filename)
{
   QImage image = QImage(filename);
   QImage glImage = QGLWidget::convertToGLFormat(image);

   loadFromBinary(glImage.bits(), glImage.width(), glImage.height());
}

void OpenGlTexture::loadFromBinary(unsigned char* data, int width, int height)
{
   width_ = width;
   height_ = height;

   textureName_ = availableTextureNames_.takeFirst();

   glBindTexture(GL_TEXTURE_2D, textureName_);

   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, 
                     GL_RGBA, GL_UNSIGNED_BYTE, data);
}

