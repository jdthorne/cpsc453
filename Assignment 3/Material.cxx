
// System

// Project
#include <Material.h>

Material::Material(Color diffuseColor,
                   Color specularColor, 
                   double specularity,
                   double reflectance)
   : diffuseColor(diffuseColor)
   , specularColor(specularColor)
   , specularity(specularity)
   , reflectance(reflectance)
{

}

Material::~Material()
{
}

Material Material::steel()
{
   static Material material = Material(Color(0.5, 0.5, 0.5),
                                       Color(0.5, 0.5, 0.5),
                                       6.0,
                                       0.75);

   return material;
}

Material Material::redSteel()
{
   static Material material = Material(Color(1, 0.25, 0.25),
                                       Color(0.5, 0.5, 0.5),
                                       6.0,
                                       0.5);

   return material;
}

Material Material::blueSteel()
{
   static Material material = Material(Color(0.25, 0.25, 1.0),
                                       Color(0.5, 0.5, 0.5),
                                       6.0,
                                       0.5);

   return material;
}

Material Material::none()
{
   static Material material = Material(Color(0, 0, 0),
                                       Color(0, 0, 0),
                                       1.0,
                                       0.0);

   return material;
}
