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
