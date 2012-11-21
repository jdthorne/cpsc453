#ifndef PROPERTYLIST_H
#define PROPERTYLIST_H

// System

// Qt
#include <QMap>
#include <QStringList>

// Project
#include <Vector.h>
#include <Color.h>
#include <Material.h>

/**
 ******************************************************************************
 *
 *                   PropertyList
 *
 * This class parses name/value pairs (such as "A = 0, 0, 1; R = 4") into 
 * easily-accessible values (e.g. Vector A = properties.vector("A"); )
 *
 ******************************************************************************
 */
class PropertyList
{

public:
   PropertyList(QString properties);
   virtual ~PropertyList();

public:
   QString string(QString key);

   Vector vector(QString key);
   Color color(QString key);
   double scalar(QString key);
   Material material(QString key);

private: // helpers

private: // members
   QMap<QString, QString> properties_;
};

#endif
