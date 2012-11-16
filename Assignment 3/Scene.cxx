
// System

// Qt
#include <QFile>
#include <QTextStream>
#include <QStringList>

// Project
#include <Scene.h>
#include <Sphere.h>
#include <Quad.h>

Scene::Scene()
   : root_(Vector(0, 0, 0), Material::none())
{
   loadFromFile("Spherical.scene");
}

Scene::~Scene()
{
}

QList<Light*>& Scene::lights()
{
   return lights_;
}

PossibleRayIntersection Scene::findFirstIntersection(Ray ray)
{
   return root_.findIntersectionWith(ray);
}

void Scene::loadFromFile(QString filename)
{
   QFile file(filename);
   file.open(QFile::ReadOnly);

   QTextStream stream(&file);
   while (!stream.atEnd())
   {
      QString line = QString(file.readLine()).trimmed();

      if (line.length() < 2 || !line.contains(":"))
      {
         continue;
      }

      QStringList components = line.split(":");

      QString type = components[0].trimmed();
      QString properties = components[1].trimmed();

      addObjectFromFile(type, properties);
   }
}

void Scene::addObjectFromFile(QString type, QString properties)
{
   if (type == "Sphere")
   {
      root_.addObject(Sphere::newFromFile(properties));
   }
   else if (type == "Quad")
   {
      root_.addObject(Quad::newFromFile(properties));
   }
   else if (type == "Light")
   {
      lights_.append(Light::newFromFile(properties));
   }
   else
   {
      qDebug("Unknown object type: '%s'", qPrintable(type));
   }
}

