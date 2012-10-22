#ifndef I_MODELSELECTOR_H
#define I_MODELSELECTOR_H

// System

// Qt
#include <QList>

// Project

class I_ModelSelector
{

public:
   virtual ~I_ModelSelector() {};

public:
   virtual QList<QString> availableModelSets() = 0;
   virtual void loadDefaultModelSet() = 0;
   virtual void loadModelSet(QString set) = 0;
   virtual void loadCustomModel(QString fromPath) = 0;
   
};

#endif
