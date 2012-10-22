
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
   , rotation_(AffineMatrix::identity())
   , scale_(1, 1, 1)
   , renderMode_(SmoothShading)
   , displayNormals_(false)
   , projectionMode_(Perspective)
   , groundModel_(NULL)
{
   connect(&modelManager_, SIGNAL(modelsChanged()), this, SLOT(handleModelsChanged()));
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
   groundModel_ = new GroundModel();

   modelManager_.loadDefaultModelSet();
}

void ModelRenderer::setFrameSize(double width, double height)
{
   width_ = width;
   height_ = height;
}

/**
 ******************************************************************************
 *
 *                   Model Loading
 *
 ******************************************************************************
 */
void ModelRenderer::handleModelsChanged()
{
   groundModel_->setZPosition(modelManager_.overallCenter().z - (modelManager_.overallSize().z / 2.0));

   Vector center = modelManager_.overallCenter();
   Vector size = modelManager_.overallSize();

   double maxSize = size.largestElement();
   double distanceRequiredToViewEntireModel = maxSize * 1.5;

   setEyePosition(Vector(distanceRequiredToViewEntireModel, 0, 0));
   setLookAtPosition(Vector(center.x, center.y, center.z));
   setUpDirection(Vector(0, 0, 1));
   
   emit renderChanged();
}

/**
 ******************************************************************************
 *
 *                   Settings
 *
 ******************************************************************************
 */
AffineMatrix ModelRenderer::rotation()
{
   return rotation_;
}

Vector ModelRenderer::eyePosition()
{
   return eyePosition_;
}

Vector ModelRenderer::lookAtPosition()
{
   return lookAtPosition_;
}

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

void ModelRenderer::setRotation(AffineMatrix rotation)
{
   rotation_ = rotation;

   emit rotationChanged();
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

void ModelRenderer::setProjectionMode(ProjectionMode mode)
{
   projectionMode_ = mode;
   emit renderChanged();
}

void ModelRenderer::setEyePosition(Vector position)
{
   eyePosition_ = position;

   emit eyePositionChanged();
   emit renderChanged();
}

void ModelRenderer::setLookAtPosition(Vector position)
{
   lookAtPosition_ = position;

   emit lookAtPositionChanged();
   emit renderChanged();
}

void ModelRenderer::setUpDirection(Vector direction)
{
   upDirection_ = direction;

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
   setupProjectionMode();

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

void ModelRenderer::setupProjectionMode()
{
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   switch (projectionMode_)
   {
      case Perspective:
      {
         gluPerspective(55.0f, (GLfloat)width_/(GLfloat)height_, 0.1f, 5000.0f);
         break;
      }

      case Parallel:
      {
         double aspect = width_ / height_;
         glOrtho(-50.0f * aspect, 50.0f * aspect, -50.0f, 50.0f, 0.1f, 5000.0f);
         break;
      }
   }
}

void ModelRenderer::setupEyePosition()
{
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   gluLookAt(eyePosition_.x, eyePosition_.y, eyePosition_.z, 
             lookAtPosition_.x, lookAtPosition_.y, lookAtPosition_.z,
             upDirection_.x, upDirection_.y, upDirection_.z);
}

void ModelRenderer::setupTransformation()
{
   glTranslatev(translation_);
   glMultMatrixa(rotation_);

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

