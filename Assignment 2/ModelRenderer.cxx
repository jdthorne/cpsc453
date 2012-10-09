
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
   : translation_(0, 0, 0)
   , scale_(1, 1, 1)
   , renderMode_(SmoothShading)
   , displayNormals_(false)
   , groundModel_(NULL)
{
   connect(&modelManager_, SIGNAL(modelsChanged()), this, SIGNAL(renderChanged()));
}

ModelRenderer::~ModelRenderer()
{
   delete groundModel_;
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
   modelManager_.loadDefaultModelSet();

   groundModel_ = new GroundModel();
   groundModel_->setZPosition(modelManager_.overallCenter().z - (modelManager_.overallSize().z / 2.0));
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
   emit renderChanged();
}

void ModelRenderer::setTranslation(Vector translation)
{
   translation_ = translation;
   emit renderChanged();
}

void ModelRenderer::setRotation(Quaternion rotation)
{
   rotation_ = rotation;
   emit renderChanged();
}

void ModelRenderer::setScale(Vector scale)
{
   scale_ = scale;
   emit renderChanged();
}

void ModelRenderer::setDisplayNormals(bool displayNormals)
{
   displayNormals_ = displayNormals;
   emit renderChanged();
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
   foreach(Model* model, modelManager_.models())
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
   Vector center = modelManager_.overallCenter();
   Vector size = modelManager_.overallSize();

   double maxSize = size.largestElement();
   double distanceRequiredToViewEntireModel = maxSize * 1.5;

   gluLookAt(distanceRequiredToViewEntireModel, 0, 0, 
             center.x, center.y, center.z,
             0, 0, 1);
}

void ModelRenderer::setupTransformation()
{
   glTranslatev(translation_);
   glRotateq(rotation_);
   glScalev(scale_);
}

void ModelRenderer::renderModel(Model& model)
{
   model.renderMesh();

   if (displayNormals_)
   {
      model.renderNormals();
   }
}

I_ModelSelector& ModelRenderer::modelSelector()
{
   return modelManager_;
}

