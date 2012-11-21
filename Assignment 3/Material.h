#ifndef MATERIAL_H
#define MATERIAL_H

// System

// Qt
#include <QMap>
#include <QString>

// Project
#include <Color.h>

class PropertyList;

/**
 ******************************************************************************
 *
 *                   Material
 *
 * Represents the properties of a surface, including diffuse color, specular
 * color and spread, reflectance, refraction, and transparency
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
   static Material* newFromFile(PropertyList& properties);

   static QMap<QString, Material*>& customMaterials();

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
