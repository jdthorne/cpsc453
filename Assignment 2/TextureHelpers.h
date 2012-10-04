#ifndef TEXTUREHELPERS_H
#define TEXTUREHELPERS_H

// System
#include <OpenGl.h>

// Qt
#include <QString>
#include <QImage>

// Project

/**
 ******************************************************************************
 *
 *                   TextureHelpers
 *
 ******************************************************************************
 */
namespace TextureHelpers
{
   QImage loadImageFromFile(QString file);

   GLuint loadTexture(QImage image);
   GLuint loadTextureFromFile(QString file);

   void generateTextureNames();
   GLuint nextOpenGlTextureName();
};

#endif
