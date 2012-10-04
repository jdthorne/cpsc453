#ifndef OPENGLTEXTURE_H
#define OPENGLTEXTURE_H

// System
#include <OpenGl.h>

// Qt
#include <QString>

// Project

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
   void loadFromPcx(QString filename);
   void loadFromQImage(QString filename);
   void loadFromBinary(char* data, int width, int height);

private: // members
   int width_;
   int height_;
   GLuint textureName_;
};

#endif
