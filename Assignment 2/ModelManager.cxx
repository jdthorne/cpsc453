
// System

// Qt
#include <QDir>

// Project
#include <Md2Model.h>
#include <ModelManager.h>

ModelManager::ModelManager()
{

}

ModelManager::~ModelManager()
{
   removeAllModels();
}

QList<QString> ModelManager::availableModelSets()
{
   QStringList results;
   foreach(QString modelSet, QDir("./models").entryList())
   {
      if (!modelSet.startsWith("."))
      {
         results.append(modelSet);
      }
   }

   return results;
}

void ModelManager::loadDefaultModelSet()
{
   models_.append(new Md2Model("models/infantry/tris.md2", "models/infantry/infantry.pcx"));
   models_.append(new Md2Model("models/infantry/weapon.md2", "models/infantry/weapon.pcx"));   
}
void ModelManager::loadModelSet(QString set)
{
   removeAllModels();

   models_.append(new Md2Model("models/" + set + "/tris.md2", "models/" + set + "/" + set + ".pcx"));

   emit modelsChanged();
}

QList<Model*>& ModelManager::models()
{
   return models_;
}

Vector ModelManager::overallCenter()
{
   return models_[0]->center();
}

Vector ModelManager::overallSize()
{
   return models_[0]->size();
}

void ModelManager::removeAllModels()
{
   foreach(Model* model, models_)
   {
      models_.removeAll(model);
      delete model;
   }
}

