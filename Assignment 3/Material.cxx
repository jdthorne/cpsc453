
// System

// Project
#include <Material.h>

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
   else
   {
      qDebug("Unknown material '%s'", qPrintable(name));
      return Material::none();
   }  
}

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
