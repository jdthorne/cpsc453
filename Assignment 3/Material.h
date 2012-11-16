#ifndef MATERIAL_H
#define MATERIAL_H

// System

// Qt
#include <QString>

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

            double reflectance = 0.0,
            double refraction = 0.0,
            double transparency = 0.0);

public:
   virtual ~Material();

   static Material steel();
   static Material redSteel();
   static Material glass();
   static Material bluePlastic();
   static Material yellowPlastic();
   static Material greenPlastic();
   static Material none();

   static Material named(QString name);

public: // members
   Color diffuseColor;
   double diffuseIntensity;

   Color specularColor;
   double specularIntensity;
   double specularSpread;

   double reflectance;
   double refraction;
   double transparency;
};

#endif
