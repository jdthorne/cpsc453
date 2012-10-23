
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

/**
 ******************************************************************************
 *
 *                   Save the frame size, so we have it for the GL perspective
 *
 ******************************************************************************
 */
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
   // Place the ground under the model's feet
   groundModel_->setZPosition(modelManager_.overallCenter().z - (modelManager_.overallSize().z / 2.0));

   // Find the center and size of the model
   Vector center = modelManager_.overallCenter();
   Vector size = modelManager_.overallSize();

   // Figure out how far away the camera needs to be
   double maxSize = size.largestElement();
   double distanceRequiredToViewEntireModel = maxSize * 1.5;

   // Place the camera and look-at positions accordingly
   setEyePosition(Vector(distanceRequiredToViewEntireModel, 0, 0));
   setLookAtPosition(Vector(center.x, center.y, center.z));
   setUpDirection(Vector(0, 0, 1));
   
   // Notify that the render has changed
   emit renderChanged();
}

/**
 ******************************************************************************
 *
 *                   Settings Accessors & Setters
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
 *                   Core rendering function
 *
 ******************************************************************************
 */
void ModelRenderer::render()
{
   // Setup
   setupProjectionMode();
   setupRenderMode();
   setupEyePosition();

   // Place the groundsheet
   renderModel(*groundModel_);

   // Apply affine transformations
   setupTransformation();

   // Render the actual models
   foreach(Model* model, modelManager_.models())
   {
      renderModel(*model);
   }
}

/**
 ******************************************************************************
 *
 *                   Render mode setup - wireframe, flat, or shaded
 *
 ******************************************************************************
 */
void ModelRenderer::setupRenderMode()
{
   switch (renderMode_)
   {
      case Wireframe:
      {
         // Wireframe just needs "GL_LINE"
         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
         break;
      }
      case FlatShading:
      {
         // Make it not wireframe, and also flat
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
         glShadeModel(GL_FLAT);
         break;
      }
      case SmoothShading:
      {
         // Make it not wireframe, and also smooth
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
         glShadeModel(GL_SMOOTH);
         break;
      }
   }
}

/**
 ******************************************************************************
 *
 *                   Set up the perspective / ortho settings
 *
 ******************************************************************************
 */
void ModelRenderer::setupProjectionMode()
{
   // Configure the projection matrix
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   // Call gluPerspective or glOrtho, depending on the setting
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

/**
 ******************************************************************************
 *
 *                   Setup the eye position
 *
 ******************************************************************************
 */
void ModelRenderer::setupEyePosition()
{
   // Configure the modelview matrix
   glMatrixMode(GL_MODELVIEW);
   jdLoadIdentity();

   // Set up the eye position
   jdLookAt(eyePosition_, lookAtPosition_, upDirection_);
}

/**
 ******************************************************************************
 *
 *                   Setup the affine transformations (translate, rotate, scale)
 *
 ******************************************************************************
 */
void ModelRenderer::setupTransformation()
{
   // Apply the transformations
   jdTranslatev(translation_);
   jdRotatea(rotation_);
   jdScalev(scale_);
}

/**
 ******************************************************************************
 *
 *                   Render the actual models
 *
 ******************************************************************************
 */
void ModelRenderer::renderModel(Model& model)
{
   // Commit the current matrix, so the transformations show up
   jdCommitMatrix();

   // Render the model
   model.renderMesh();

   // Render the normals, if necessary
   if (displayNormals_)
   {
      model.renderNormals();
   }
}

/**
 ******************************************************************************
 *
 *                   Accessor for the model selector (used by Sidebar)
 *
 ******************************************************************************
 */
I_ModelSelector& ModelRenderer::modelSelector()
{
   return modelManager_;
}


/**
 ******************************************************************************
 *
 *                   Force a redraw, in case anything else changes
 *
 ******************************************************************************
 */
void ModelRenderer::forceRedraw()
{
   emit renderChanged();
}

