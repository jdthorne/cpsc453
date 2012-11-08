
// System

// Project
#include <Material.h>

Material::Material(Color diffuseColor,
                   double diffuseIntensity,

                   Color specularColor, 
                   double specularIntensity,
                   double specularSpread,

                   double reflectance)
   : diffuseColor(diffuseColor)
   , diffuseIntensity(diffuseIntensity)

   , specularColor(specularColor)
   , specularIntensity(specularIntensity)
   , specularSpread(specularSpread)

   , reflectance(reflectance)
{

}

Material::~Material()
{
}

Material Material::steel()
{
   static Material material = Material(Color(0.75, 0.75, 0.75),
                                       0.75,

                                       Color(0.5, 0.5, 0.5),
                                       0.5,
                                       6.0,

                                       0.75);

   return material;
}

Material Material::redSteel()
{
   static Material material = Material(Color(1, 0.25, 0.25),
                                       0.5,

                                       Color(1, 1, 1),
                                       0.5,
                                       6.0,

                                       0.75);

   return material;
}

Material Material::blueSteel()
{
   static Material material = Material(Color(0.25, 0.25, 1.0),
                                       0.5,

                                       Color(1, 1, 1),
                                       0.5,
                                       20.0,

                                       0.75);

   return material;
}

Material Material::none()
{
   static Material material = Material(Color(0, 0, 0),
                                       0.5,

                                       Color(0.5, 0.5, 0.5),
                                       0.5,
                                       6.0,

                                       0.75);

   return material;
}
