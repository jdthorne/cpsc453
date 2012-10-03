
// 3rdparty
#include <md2.h>

// System
#include <OpenGl.h>

// Qt
#include <QList>

// Project
#include <ModelRenderer.h>
#include <RenderHelpers.h>
#include <Vector.h>

#include <GroundModel.h>
#include <Md2Model.h>

using namespace RenderHelpers;

ModelRenderer::ModelRenderer()
   : renderMode_(SmoothShading)
   , displayNormals_(false)
   , groundModel_(NULL)
{
}

ModelRenderer::~ModelRenderer()
{
   delete groundModel_;

   foreach(Model* model, models_)
   {
      models_.removeAll(model);
      delete model;
   }
}

/**
 ******************************************************************************
 *
 *                   Setup
 *
 *    Setup can't Happen until OpenGL is ready, so we need a separate function
 *    for it.
 *
 ******************************************************************************
 */
void ModelRenderer::initialize()
{
   models_.append(new Md2Model("models/bobafett/tris.md2", "models/bobafett/ROTJ_Fett.pcx"));
   //models_.append(new Md2Model("models/bobafett/calvin_w_bfg.md2", "models/calvin/calvin_w_bfg.bmp"));   

   groundModel_ = new GroundModel();
   groundModel_->setZPosition(models_[0]->center().z - (models_[0]->size().z / 2.0));
}

/**
 ******************************************************************************
 *
 *                   Settings
 *
 ******************************************************************************
 */
void ModelRenderer::setRenderMode(RenderMode mode)
{
   renderMode_ = mode;
   emit optionsChanged();
}

void ModelRenderer::setTranslation(Vector translation)
{
   translation_ = translation;
   emit optionsChanged();
}

void ModelRenderer::setDisplayNormals(bool displayNormals)
{
   displayNormals_ = displayNormals;
   emit optionsChanged();
}

/**
 ******************************************************************************
 *
 *                   Rendering
 *
 ******************************************************************************
 */
void ModelRenderer::render()
{
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   setupRenderMode();
   setupEyePosition();
   renderModel(*groundModel_);

   setupTransformation();
   foreach(Model* model, models_)
   {
      renderModel(*model);
   }
}

void ModelRenderer::setupRenderMode()
{
   switch (renderMode_)
   {
      case Wireframe:
      {
         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
         break;
      }
      case FlatShading:
      {
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
         glShadeModel(GL_FLAT);
         break;
      }
      case SmoothShading:
      {
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
         glShadeModel(GL_SMOOTH);
         break;
      }
   }
}

void ModelRenderer::setupEyePosition()
{
   Vector center = models_[0]->center();
   Vector size = models_[0]->size();

   double maxSize = size.largestElement();
   double distanceRequiredToViewEntireModel = maxSize * 1.5;

   gluLookAt(distanceRequiredToViewEntireModel, 0, 0, 
             center.x, center.y, center.z,
             0, 0, 1);
}

void ModelRenderer::setupTransformation()
{
   glTranslatev(translation_);
}

void ModelRenderer::renderModel(Model& model)
{
   model.renderMesh();

   if (displayNormals_)
   {
      model.renderNormals();
   }
}

