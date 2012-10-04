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
