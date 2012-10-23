#ifndef OPENGLTEXTURE_H
#define OPENGLTEXTURE_H

// System
#include <OpenGl.h>

// Qt
#include <QString>
#include <QList>

// Project

typedef GLuint GlTextureName;

/**
 ******************************************************************************
 *
 *                   OpenGlTexture
 *
 *  This class represents an OpenGL texture, and allows you to easily turn
 *  a filename into an OpenGL texture "name".
 *
 ******************************************************************************
 */
class OpenGlTexture
{

public:
   OpenGlTexture(QString filename);
   virtual ~OpenGlTexture();

public:
   void bind();

   double width();
   double height();

private: // helpers
   void ensureOpenGlTexturesAreInitialized();

   void loadFromFile(QString filename);
   void loadFromPcx(QString filename);
   void loadFromQImage(QString filename);
   void loadFromBinary(unsigned char* data, int width, int height);

private: // members
   static QList<GlTextureName> availableTextureNames_;

   int width_;
   int height_;
   GlTextureName textureName_;
};

#endif
