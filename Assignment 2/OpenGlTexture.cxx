
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
   // Don't initialize texture array more than once
   static bool texturesAreInitialized = false;
   if (texturesAreInitialized)
   {
      return;
   }

   // Create the names
   const int maxTextures = 32;
   GlTextureName names[maxTextures];

   // Gen the textures
   glGenTextures(maxTextures, names);

   // Add all the names to the "available" queue
   for (int i = 0; i < maxTextures; i++)
   {
      availableTextureNames_.append(names[i]);
   }

   // Don't initialize more than once
   texturesAreInitialized = true;
}

/**
 ******************************************************************************
 *
 *                   Load a texture from a file
 *
 ******************************************************************************
 */
void OpenGlTexture::loadFromFile(QString filename)
{
   // Load via QImage or PCX, depending on file format
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

/**
 ******************************************************************************
 *
 *                   Load from a PCX file
 *
 ******************************************************************************
 */
void OpenGlTexture::loadFromPcx(QString file)
{
   int width, height;
   unsigned char* pixels = NULL;

   // Use pcx.h to get binary data
   int result = LoadFilePCX(qPrintable(file), &pixels, &width, &height, true);

   // Ensure it loaded correctly
   if (result == 0)
   {
      qDebug("[OpenGlTexture] Error loading '%s' - texture will not be available", qPrintable(file));
      return;
   }

   // Load the raw data into OpenGL
   loadFromBinary(pixels, width, height);
}

/**
 ******************************************************************************
 *
 *                   Load from a file that Qt understands
 *
 ******************************************************************************
 */
void OpenGlTexture::loadFromQImage(QString filename)
{  
   qDebug("Loaded texture '%s'", qPrintable(filename));

   // Use Qt to get an image
   QImage image = QImage(filename);

   // Make sure it's in the format OpenGL likes
   QImage glImage = QGLWidget::convertToGLFormat(image);

   // Load the binary data
   loadFromBinary(glImage.bits(), glImage.width(), glImage.height());
}

/**
 ******************************************************************************
 *
 *                   Load binary data into OpenGL
 *
 ******************************************************************************
 */
void OpenGlTexture::loadFromBinary(unsigned char* data, int width, int height)
{
   width_ = width;
   height_ = height;

   // Find the next available texture name
   textureName_ = availableTextureNames_.takeFirst();

   // Bind the texture
   glBindTexture(GL_TEXTURE_2D, textureName_);

   // Configure texture parameters
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   // Build the actual mipmaps (i.e. load the texture into OpenGL)
   gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, 
                     GL_RGBA, GL_UNSIGNED_BYTE, data);
}

