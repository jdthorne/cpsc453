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
            double diffuseIntensity,

            Color specularColor, 
            double specularIntensity,
            double specularSpread,

            double reflectance);

public:
   virtual ~Material();

   static Material steel();
   static Material redSteel();
   static Material blueSteel();
   static Material none();

public: // members
   Color diffuseColor;
   double diffuseIntensity;

   Color specularColor;
   double specularIntensity;
   double specularSpread;

   double reflectance;
};

#endif
