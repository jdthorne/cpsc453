#ifndef IMAGE_H
#define IMAGE_H

// System
#include <string>

// Project

/**
 ******************************************************************************
 *
 * \brief            Image
 *
 ******************************************************************************
 */
class Image
{

public:
   Image();
   Image(std::string filename);
   ~Image();

public:

private: // helpers
   void loadFromFile(std::string filename);

private: // members
   char* imageData_;
};

#endif
