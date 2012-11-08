#ifndef MATERIAL_H
#define MATERIAL_H

// System

// Project
#include <Color.h>

/**
 ******************************************************************************
 *
 *                   Material
 *
 ******************************************************************************
 */
class Material
{
   Material(Color diffuseColor,
            Color specularColor, 
            double specularity,
            double reflectance);
   virtual ~Material();

public:
   static Material& redSteel();
   static Material& blueSteel();

public: // members
   const Color diffuseColor;
   const Color specularColor;
   const double specularity;

   const double reflectance;
};

#endif
