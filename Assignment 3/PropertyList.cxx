
// System

// Project
#include <PropertyList.h>

PropertyList::PropertyList(QString properties)
{
   foreach (QString property, properties.split(";"))
   {
      QStringList components = property.split("=");
      QString key = components[0].trimmed();
      QString value = components[1].trimmed();

      properties_[key] = value;
   }
}

PropertyList::~PropertyList()
{
}

Vector PropertyList::vector(QString key)
{
   QStringList components = properties_[key].split(",");

   double x = components[0].trimmed().toDouble();
   double y = components[1].trimmed().toDouble();
   double z = components[2].trimmed().toDouble();

   return Vector(x, y, z);
}

Color PropertyList::color(QString key)
{
   QStringList components = properties_[key].split(",");

   double r = components[0].trimmed().toDouble();
   double g = components[1].trimmed().toDouble();
   double b = components[2].trimmed().toDouble();

   return Color(r, g, b);
}

Material PropertyList::material(QString key)
{
   return Material::named(string(key));
}

double PropertyList::scalar(QString key)
{
   return properties_[key].toDouble();
}

QString PropertyList::string(QString key)
{
   if (!properties_.contains(key))
   {
      qDebug("[PropertyList] No such property '%s'", qPrintable(key));
   }

   return properties_[key];
}

