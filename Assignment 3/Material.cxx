
// System

// Project
#include <Material.h>
#include <PropertyList.h>

Material::Material(Color diffuseColor,
                   double diffuseIntensity,

                   Color specularColor, 
                   double specularIntensity,
                   double specularSpread,

                   double reflectance,
                   double refraction,
                   double transparency)

   : diffuseColor(diffuseColor)
   , diffuseIntensity(diffuseIntensity)

   , specularColor(specularColor)
   , specularIntensity(specularIntensity)
   , specularSpread(specularSpread)

   , reflectance(reflectance)
   , refraction(refraction)
   , transparency(transparency)
{
}

Material::~Material()
{
}

/**
 ******************************************************************************
 *
 *                   Store custom materials
 *
 ******************************************************************************
 */

QMap<QString,Material*>& Material::customMaterials()
{
   static QMap<QString, Material*> customMaterials;

   return customMaterials;
}

/**
 ******************************************************************************
 *
 *                   Load a material from a definition
 *
 ******************************************************************************
 */
Material* Material::newFromFile(PropertyList& properties)
{
   return new Material(properties.color("Diffuse"), 
                       properties.scalar("DiffuseK"),

                       properties.color("Specular"), 
                       properties.scalar("SpecularK"),
                       properties.scalar("SpecularAlpha"),

                       properties.scalar("Reflectance"),
                       properties.scalar("Refraction"),
                       properties.scalar("Transparency"));
}

/**
 ******************************************************************************
 *
 *                   Return a material from a name
 *
 ******************************************************************************
 */
Material Material::named(QString name)
{
   if (name == "steel")
   {
      return Material::steel();
   }
   else if (name == "redSteel")
   {
      return Material::redSteel();
   }
   else if (name == "bluePlastic")
   {
      return Material::bluePlastic();
   }
   else if (name == "yellowPlastic")
   {
      return Material::yellowPlastic();
   }
   else if (name == "greenPlastic")
   {
      return Material::greenPlastic();
   }
   else if (name == "glass")
   {
      return Material::glass();
   }
   else if (customMaterials().contains(name))
   {
      return *(customMaterials()[name]);
   }
   else
   {
      qDebug("Unknown material '%s'", qPrintable(name));
      return Material::none();
   }  
}

/**
 ******************************************************************************
 *
 *                   Simple, reflective grey steel
 *
 ******************************************************************************
 */
Material Material::steel()
{
   static Material material = Material(Color(0.75, 0.75, 0.75),
                                       0.75,

                                       Color(0.5, 0.5, 0.5),
                                       0.5,
                                       75.0,

                                       0.5);

   return material;
}

/**
 ******************************************************************************
 *
 *                   Red Steel
 *
 ******************************************************************************
 */
Material Material::redSteel()
{
   static Material material = Material(Color(1, 0.25, 0.25),
                                       0.5,

                                       Color(1, 1, 1),
                                       0.5,
                                       75.0,

                                       0.25);

   return material;
}

/**
 ******************************************************************************
 *
 *                   Translucent glass
 *
 ******************************************************************************
 */
Material Material::glass()
{
   static Material material = Material(Color(0.5, 0.5, 0.5),
                                       0.8,

                                       // Specular
                                       Color(1, 1, 1),
                                       0.6,
                                       75.0,

                                       // Reflection
                                       0.0,

                                       // Refraction
                                       1.2,
                                       0.75);

   return material;
}

/**
 ******************************************************************************
 *
 *                   Blue plasticey material
 *
 ******************************************************************************
 */
Material Material::bluePlastic()
{
   static Material material = Material(Color(0.35, 0.35, 1.0),
                                       0.5,

                                       Color(1, 1, 1),
                                       0.5,
                                       15.0,

                                       0.0);

   return material;
}

/**
 ******************************************************************************
 *
 *                   Yellow plastic
 *
 ******************************************************************************
 */
Material Material::yellowPlastic()
{
   static Material material = Material(Color(1.0, 1.0, 0.35),
                                       0.5,

                                       Color(1, 1, 1),
                                       0.5,
                                       15.0,

                                       0.0);

   return material;
}

/**
 ******************************************************************************
 *
 *                   Green plastic
 *
 ******************************************************************************
 */
Material Material::greenPlastic()
{
   static Material material = Material(Color(0.35, 1.0, 0.35),
                                       0.5,

                                       Color(1, 1, 1),
                                       0.5,
                                       15.0,

                                       0.0);

   return material;
}

/**
 ******************************************************************************
 *
 *                   "Null" material
 *
 ******************************************************************************
 */
Material Material::none()
{
   static Material material = Material(Color(0, 0, 0),
                                       0.5,

                                       Color(0.5, 0.5, 0.5),
                                       0.5,
                                       6.0,

                                       0.0);

   return material;
}
