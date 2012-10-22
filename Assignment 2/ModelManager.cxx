
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

   emit modelsChanged();
}
void ModelManager::loadModelSet(QString set)
{
   loadCustomModel("models/" + set + "/tris.md2");
}

void ModelManager::loadCustomModel(QString path)
{
   removeAllModels();

   // Load the model
   models_.append(new Md2Model(path, findSkinForModel(path)));

   // Load the weapon
   QString folder = QFileInfo(path).absoluteDir().absolutePath();
   QString weaponModel = folder + "/weapon.md2";
   QString weaponSkin = folder + "/weapon.pcx";
   models_.append(new Md2Model(weaponModel, weaponSkin));

   emit modelsChanged();
}

QString ModelManager::findSkinForModel(QString modelPath)
{
   QDir folder = QFileInfo(modelPath).absoluteDir();
   QString folderPath = folder.absolutePath();

   // First, try the same filename
   QString skinWithSameFilename = modelPath.replace(".md2", ".pcx");
   if (QFile::exists(skinWithSameFilename))
   {
      return skinWithSameFilename;
   }

   // Then try the folder name
   QString sameAsFolderName = folderPath + "/" + folder.dirName() + ".pcx";
   if (QFile::exists(sameAsFolderName))
   {
      return sameAsFolderName;
   }

   // Next, try "skin.pcx"
   QString skinPcx = folderPath + "/skin.pcx";
   if (QFile::exists(skinPcx))
   {
      return skinPcx;
   }

   // Finally, try the first PCX file in the folder 
   foreach(QString skinFile, QDir(folder).entryList())
   {
      if (skinFile.endsWith(".pcx") || skinFile.endsWith(".bmp"))
      {
         return skinFile;
      }
   }

   qDebug("[findSkinForModel] Couldn't find skin for %s", qPrintable(modelPath));
   return QString();
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

