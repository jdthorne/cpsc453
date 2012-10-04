
// System

// Project
#include <OpenGlTexture.h>

OpenGlTexture::OpenGlTexture(QString filename)
{

}

OpenGlTexture::~OpenGlTexture()
{
}

/**
 ******************************************************************************
 *
 *                   Loading
 *
 ******************************************************************************
 */
void OpenGlTexture::loadFromPcx(QString filename)
{
   printf("Warning: [OpenGlTexture] 'loadFromPcx(QString filename)' is not implemented\n");
}

void OpenGlTexture::loadFromQImage(QString filename)
{
   printf("Warning: [OpenGlTexture] 'loadFromQImage(QString filename)' is not implemented\n");
}

void OpenGlTexture::loadFromBinary(char* data, int width, int height)
{
   printf("Warning: [OpenGlTexture] 'loadFromBinary(char* data, int width, int height)' is not implemented\n");
}

