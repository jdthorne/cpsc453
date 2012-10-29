
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

/**
 ******************************************************************************
 *
 *                   Gets the list of available models
 *
 ******************************************************************************
 */
QList<QString> ModelManager::availableModelSets()
{
   QStringList results;

   // Loop through the subfolders of "./models"
   foreach(QString modelSet, QDir("./models").entryList())
   {
      // Ignore dotfiles
      if (modelSet.startsWith("."))
      {
         continue;
      }

      // Add the model to results
      results.append(modelSet);
   }

   return results;
}

/**
 ******************************************************************************
 *
 *                   Load the default models (happens on startup)
 *
 ******************************************************************************
 */
void ModelManager::loadDefaultModelSet()
{
   // Load the "infantry" model
   models_.append(new Md2Model("models/infantry/tris.md2", "models/infantry/infantry.pcx"));
   models_.append(new Md2Model("models/infantry/weapon.md2", "models/infantry/weapon.pcx"));   

   emit modelsChanged();
}

/**
 ******************************************************************************
 *
 *                   Load a model set from availableModelSets()
 *
 ******************************************************************************
 */
void ModelManager::loadModelSet(QString set)
{
   QString path = findMeshForModel("./models/" + set);

   // Clear any existing models
   removeAllModels();

   // Load the model
   models_.append(new Md2Model(path, findSkinForModel(path)));

   // Find the weapon
   QString folder = QFileInfo(path).absoluteDir().absolutePath();
   QString weaponModel = folder + "/weapon.md2";
   QString weaponSkin = findSkinForModel(weaponModel);

   // Load the weapon if it exists
   if (QFile::exists(weaponModel) && QFile::exists(weaponSkin))
   {
      models_.append(new Md2Model(weaponModel, weaponSkin));
   }

   // Notify that the models have changed
   emit modelsChanged();
}

/**
 ******************************************************************************
 *
 *                   Load a model at an arbitrary path
 *
 ******************************************************************************
 */
void ModelManager::loadCustomModel(QString modelPath, QString modelSkinPath, 
                                   QString weaponPath, QString weaponSkinPath)
{
   // Clear any existing models
   removeAllModels();

   // Load the model, if it exists
   if (QFile::exists(modelPath))
   {
      models_.append(new Md2Model(modelPath, modelSkinPath));
   }

   // Load the weapon, if it exists
   if (QFile::exists(weaponPath))
   {
      models_.append(new Md2Model(weaponPath, weaponSkinPath));
   }

   // Notify that the models have changed
   emit modelsChanged();
}

/**
 ******************************************************************************
 *
 *                   Helper to search for the path for a given model
 *
 ******************************************************************************
 */
QString ModelManager::findMeshForModel(QString folderPath)
{
   // Ensure we have valid input
   if (folderPath == "")
   {
      return "";
   }

   // Figure out the name of the folder (e.g. /foo/bar/baz ==> baz)
   QString folderName = folderPath.split("/")[ folderPath.split("/").length() - 1 ];

   // Try "tris.md2"
   QString meshWithTris = folderPath + "/tris.md2";
   if (QFile::exists(meshWithTris))
   {
      return meshWithTris;
   }

   // Try "folder.md2"
   QString meshWithFolder = folderPath + "/" + folderName + ".md2";
   if (QFile::exists(meshWithFolder))
   {
      return meshWithFolder;
   }

   // Give up
   return QString();
}

/**
 ******************************************************************************
 *
 *                   Helper to search for the skin for a given model
 *
 ******************************************************************************
 */
QString ModelManager::findSkinForModel(const QString modelPath)
{
   QDir folder = QFileInfo(modelPath).absoluteDir();
   QString folderPath = folder.absolutePath();

   // Try looking for the same filename, but with .pcx instead of .md2
   // e.g. ./models/infantry/tris.pcx
   QString skinWithSameFilename = modelPath;
   skinWithSameFilename = skinWithSameFilename.replace(".md2", ".pcx").replace(".MD2", ".PCX");
   if (QFile::exists(skinWithSameFilename))
   {
      return skinWithSameFilename;
   }

   // Try again, but with .bmp instead of .pcx
   skinWithSameFilename = modelPath;
   skinWithSameFilename = skinWithSameFilename.replace(".md2", ".bmp").replace(".MD2", ".BMP");
   if (QFile::exists(skinWithSameFilename))
   {
      return skinWithSameFilename;
   }

   // Next, try a skin with the same name as the folder
   // e.g. ./models/infantry/infantry.pcx
   QString sameAsFolderName = folderPath + "/" + folder.dirName() + ".pcx";
   if (QFile::exists(sameAsFolderName))
   {
      return sameAsFolderName;
   }

   // Next, try "skin.pcx"
   // e.g. ./models/infantry/skin.pcx
   QString skinPcx = folderPath + "/skin.pcx";
   if (QFile::exists(skinPcx))
   {
      return skinPcx;
   }

   // Finally, just grab the first image file in the folder
   foreach(QString skinFile, QDir(folder).entryList())
   {
      if (skinFile.endsWith(".pcx") || skinFile.endsWith(".bmp"))
      {
         return folderPath + "/" + skinFile;
      }
   }

   // If that doesn't work, give up
   qDebug("[findSkinForModel] Couldn't find skin for '%s'", qPrintable(modelPath));
   return QString();
}

/**
 ******************************************************************************
 *
 *                   Return the list of models
 *
 ******************************************************************************
 */
QList<Model*>& ModelManager::models()
{
   return models_;
}

/**
 ******************************************************************************
 *
 *                   Return the overall center of the models
 *
 ******************************************************************************
 */
Vector ModelManager::overallCenter()
{
   if (models_.count() == 0)
   {
      return Vector(0, 0, 0);
   }

   return models_[0]->center();
}

/**
 ******************************************************************************
 *
 *                   Return the overall size of the models
 *
 ******************************************************************************
 */
Vector ModelManager::overallSize()
{
   if (models_.count() == 0)
   {
      return Vector(50, 50, 50);
   }

   return models_[0]->size();
}

/**
 ******************************************************************************
 *
 *                   Remove all of the currently loaded models.
 *
 ******************************************************************************
 */
void ModelManager::removeAllModels()
{
   foreach(Model* model, models_)
   {
      models_.removeAll(model);
      delete model;
   }
}

