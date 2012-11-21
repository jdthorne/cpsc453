
// System

// Qt
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QCoreApplication>

// Project
#include <Scene.h>
#include <Sphere.h>
#include <Quad.h>
#include <Cylinder.h>
#include <Triangle.h>

Scene::Scene(QString file)
   : ambientLight_(0.1, 0.1, 0.1)
   , root_(Vector(0, 0, 0), Material::none())
{
   loadFromFile(file);
}

Scene::~Scene()
{
}

/**
 ******************************************************************************
 *
 *                   Return all lights
 *
 ******************************************************************************
 */
QList<Light*>& Scene::lights()
{
   return lights_;
}

/**
 ******************************************************************************
 *
 *                   Return ambient color
 *
 ******************************************************************************
 */
Color Scene::ambientLight()
{
   return ambientLight_;
}

/**
 ******************************************************************************
 *
 *                   Return first intersection from a ray
 *
 ******************************************************************************
 */
PossibleRayIntersection Scene::findFirstIntersection(Ray ray)
{
   return root_.findIntersectionWith(ray);
}

/**
 ******************************************************************************
 *
 *                   Load in the scene from a file
 *
 ******************************************************************************
 */
void Scene::loadFromFile(QString filename)
{
   // Make a QFile
   QFile file(filename);
   file.open(QFile::ReadOnly);

   // Make a stream
   QTextStream stream(&file);

   // Read each line...
   while (!stream.atEnd())
   {
      QString line = QString(file.readLine()).trimmed();

      // Ignore short, invalid, or comment lines
      if (line.length() < 2 || !line.contains(":") || line.startsWith("#"))
      {
         continue;
      }

      // Break into components
      QStringList components = line.split(":");

      QString type = components[0].trimmed();
      QString properties = components[1].trimmed();

      // Add the object
      addObjectFromFile(type, properties);
   }
}

/**
 ******************************************************************************
 *
 *                   Add an object from a type and properties list
 *
 ******************************************************************************
 */
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
   else if (type == "Cylinder")
   {
      root_.addObject(Cylinder::newFromFile(properties));
   }
   else if (type == "Triangle")
   {
      root_.addObject(Triangle::newFromFile(properties));
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

