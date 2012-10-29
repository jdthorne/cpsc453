#ifndef MODELMANAGER_H
#define MODELMANAGER_H

// System

// Qt
#include <QObject>
#include <QList>

// Project
#include <I_ModelSelector.h>
#include <Vector.h>

class Model;

/**
 ******************************************************************************
 *
 *                   ModelManager
 *
 *  This class is responsible for loading models from disk.
 *
 ******************************************************************************
 */
class ModelManager : public QObject, public I_ModelSelector
{
   Q_OBJECT

public:
   ModelManager();
   virtual ~ModelManager();

public:
   virtual QList<QString> availableModelSets();
   virtual void loadDefaultModelSet();
   virtual void loadModelSet(QString set);
   virtual void loadCustomModel(QString modelPath, QString modelSkinPath, 
                                QString weaponPath, QString weaponSkinPath);

   Vector overallCenter();
   Vector overallSize();

   QList<Model*>& models();

signals:
   void modelsChanged();

private: // helpers
   void removeAllModels();
   QString findMeshForModel(QString path);
   QString findSkinForModel(QString path);

private: // members
   QList<Model*> models_;
};

#endif
