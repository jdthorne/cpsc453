
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

ModelRenderer::ModelRenderer(ModelManager& manager)
   // Initialize settings to sane defaults
   : translation_(0, 0, 0)
   , rotation_(AffineMatrix::identity())
   , scale_(1, 1, 1)
   , renderMode_(SmoothShading)
   , alternativeMode_(NormalRender)
   , displayNormals_(false)
   , projectionMode_(Perspective)

   // Initialize members
   , groundModel_(NULL)
   , modelManager_(manager)
{
   // Ensure we know about model changes (so we can trigger a redraw)
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
 *    for it, instead of doing it in the constructor.
 *
 ******************************************************************************
 */
void ModelRenderer::initialize()
{
   groundModel_ = new GroundModel();
}

/**
 ******************************************************************************
 *
 *                   Save the viewport, so we have it for glViewport and
 *                   glPerspective
 *
 ******************************************************************************
 */
void ModelRenderer::setViewport(int x, int y, int width, int height)
{
   x_ = x;
   y_ = y;
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
}

/**
 ******************************************************************************
 *
 *                   Automatically set up the camera
 *
 ******************************************************************************
 */
void ModelRenderer::configureMainView()
{
   // Place the camera and look-at positions to see the model nicely
   setEyePosition(Vector(distanceRequiredToSeeEntireModel(), 0, 0));
   setLookAtPosition(modelManager_.overallCenter());
   setUpDirection(Vector(0, 0, 1));
}

void ModelRenderer::configureTopView()
{
   // Place the camera and look-at positions to see the model from the top
   setEyePosition(Vector(0, 0, distanceRequiredToSeeEntireModel()));
   setLookAtPosition(modelManager_.overallCenter());
   setUpDirection(Vector(1, 0, 0));
}

void ModelRenderer::configureSideView()
{
   // Place the camera and look-at positions to see the model from the side
   setEyePosition(Vector(0, distanceRequiredToSeeEntireModel(), 0));
   setLookAtPosition(modelManager_.overallCenter());
   setUpDirection(Vector(0, 0, 1));
}

void ModelRenderer::configureFrontView()
{
   // Place the camera and look-at positions to see the model from the front
   setEyePosition(Vector(distanceRequiredToSeeEntireModel(), 0, 0));
   setLookAtPosition(modelManager_.overallCenter());
   setUpDirection(Vector(0, 0, 1));
}

/**
 ******************************************************************************
 *
 *                   Helper to determine how far away the camera needs to be
 *                   in order to see the whole model
 *
 ******************************************************************************
 */
double ModelRenderer::distanceRequiredToSeeEntireModel()
{
   // Find the size of the model
   Vector size = modelManager_.overallSize();

   // Figure out how far away the camera needs to be
   double maxSize = size.largestElement();
   double distanceRequiredToViewEntireModel = maxSize * 1.75;

   return distanceRequiredToViewEntireModel;
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

void ModelRenderer::setAlternativeMode(AlternativeMode mode)
{
   alternativeMode_ = mode;
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
   // Configure the viewport
   glViewport(x_, y_, width_, height_);

   // Configure the projection matrix
   glMatrixMode(GL_PROJECTION);
   jdLoadIdentity();

   // Call perspective or ortho, depending on the setting
   switch (projectionMode_)
   {
      case Perspective:
      {
         jdPerspective(55.0f, (GLfloat)width_/(GLfloat)height_, 0.1f, 5000.0f);
         break;
      }

      case Parallel:
      {
         // Calculate aspect ratio for maximum viewability
         double xAspect = 1.0;
         double yAspect = (double)height_ / (double)width_;
         if (yAspect < 1.0)
         {
            xAspect = 1.0 / yAspect;
            yAspect = 1.0;
         }

         // Set up the orthographic viewport
         double size = 50.0f;
         jdOrtho(-size * xAspect, size * xAspect, -size * yAspect, size * yAspect, 0.1f, 5000.0f);
         break;
      }
   }

   jdCommitMatrix();
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
   jdCommitMatrix();
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

   // Commit the current matrix, so the transformations show up
   jdCommitMatrix();
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
   // Render the model
   model.renderMesh(alternativeMode_);

   // Render the normals, if necessary
   if (displayNormals_)
   {
      model.renderNormals();
   }
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

