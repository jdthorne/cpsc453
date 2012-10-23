
// System

// Qt
#include <QVBoxLayout>
#include <QRadioButton>
#include <QGroupBox>
#include <QFileDialog>

// UIC
#include <SidebarUi.ui.h>

// Project
#include <Vector.h>
#include <Sidebar.h>
#include <RenderHelpers.h>
#include <SliderSpinboxController.h>
#include <I_RenderOptions.h>
#include <I_ModelSelector.h>

using namespace RenderHelpers;

Sidebar::Sidebar(I_RenderOptions& options, I_ModelSelector& modelSelector)
   : options_(options)
   , modelSelector_(modelSelector)
{
   // Setup the Qt UI file
   ui_ = new Ui_SidebarUi();
   ui_->setupUi(this);
   setMinimumWidth(290);

   // Add the model choices to the list
   foreach(QString modelSet, modelSelector_.availableModelSets())
   {
      ui_->selectModel->addItem(modelSet);
   }
   ui_->selectModel->setCurrentIndex(modelSelector_.availableModelSets().count() - 1);
   ui_->selectModel->addItem("Browse...");
   connect(ui_->selectModel, SIGNAL(currentIndexChanged(int)), this, SLOT(handleModelSelected()));

   // Create controllers for the Affine Transformations tab
   xTranslation_ = new SliderSpinboxController(ui_->xTranslation, ui_->xTranslationSpin, this, SLOT(handleTranslationChanged()));
   yTranslation_ = new SliderSpinboxController(ui_->yTranslation, ui_->yTranslationSpin, this, SLOT(handleTranslationChanged()));
   zTranslation_ = new SliderSpinboxController(ui_->zTranslation, ui_->zTranslationSpin, this, SLOT(handleTranslationChanged()));

   xScale_ = new SliderSpinboxController(ui_->xScale, ui_->xScaleSpin, this, SLOT(handleScaleChanged()));
   yScale_ = new SliderSpinboxController(ui_->yScale, ui_->yScaleSpin, this, SLOT(handleScaleChanged()));
   zScale_ = new SliderSpinboxController(ui_->zScale, ui_->zScaleSpin, this, SLOT(handleScaleChanged()));
   uScale_ = new SliderSpinboxController(ui_->uScale, ui_->uScaleSpin, this, SLOT(handleScaleChanged()));

   // Create controllers for the View Transformations tab
   xView_ = new SliderSpinboxController(ui_->xView, ui_->xViewSpin, this, SLOT(handleEyePositionChanged()));
   yView_ = new SliderSpinboxController(ui_->yView, ui_->yViewSpin, this, SLOT(handleEyePositionChanged()));
   zView_ = new SliderSpinboxController(ui_->zView, ui_->zViewSpin, this, SLOT(handleEyePositionChanged()));

   xLookAt_ = new SliderSpinboxController(ui_->xLookAt, ui_->xLookAtSpin, this, SLOT(handleLookAtPositionChanged()));
   yLookAt_ = new SliderSpinboxController(ui_->yLookAt, ui_->yLookAtSpin, this, SLOT(handleLookAtPositionChanged()));
   zLookAt_ = new SliderSpinboxController(ui_->zLookAt, ui_->zLookAtSpin, this, SLOT(handleLookAtPositionChanged()));

   xUp_ = new SliderSpinboxController(ui_->xUp, ui_->xUpSpin, this, SLOT(handleUpDirectionChanged()));
   yUp_ = new SliderSpinboxController(ui_->yUp, ui_->yUpSpin, this, SLOT(handleUpDirectionChanged()));
   zUp_ = new SliderSpinboxController(ui_->zUp, ui_->zUpSpin, this, SLOT(handleUpDirectionChanged()));

   // Connect the Render Options tab
   connect(ui_->showNormals, SIGNAL(toggled(bool)), this, SLOT(handleShowNormalsChanged()));

   connect(ui_->wireframe, SIGNAL(toggled(bool)), this, SLOT(handleRenderModeChanged()));
   connect(ui_->flat, SIGNAL(toggled(bool)), this, SLOT(handleRenderModeChanged()));
   connect(ui_->smooth, SIGNAL(toggled(bool)), this, SLOT(handleRenderModeChanged()));

   connect(ui_->perspective, SIGNAL(toggled(bool)), this, SLOT(handleProjectionChanged()));
   connect(ui_->parallel, SIGNAL(toggled(bool)), this, SLOT(handleProjectionChanged()));

   // If renderOptions changes (e.g. when auto-centering a model), make sure we update too
   connect(&options_, SIGNAL(eyePositionChanged()), this, SLOT(handleEyePositionChangedByRenderOptions()));
   connect(&options_, SIGNAL(lookAtPositionChanged()), this, SLOT(handleLookAtPositionChangedByRenderOptions()));
}

Sidebar::~Sidebar()
{
}

/**
 ******************************************************************************
 *
 *                   Set the Render Mode (Wireframe, Flat, Smooth)
 *
 ******************************************************************************
 */
void Sidebar::handleRenderModeChanged()
{
   if (ui_->wireframe->isChecked())
   {
      options_.setRenderMode(Wireframe);
   }
   else if (ui_->flat->isChecked())
   {
      options_.setRenderMode(FlatShading);
   }
   else if (ui_->smooth->isChecked())
   {
      options_.setRenderMode(SmoothShading);
   }
}

/**
 ******************************************************************************
 *
 *                   Affine Translation
 *
 ******************************************************************************
 */
void Sidebar::handleTranslationChanged()
{
   Vector translation = Vector(xTranslation_->value(),
                               yTranslation_->value(),
                               zTranslation_->value());

   options_.setTranslation(translation);
}

/**
 ******************************************************************************
 *
 *                   Affine Scale
 *
 ******************************************************************************
 */
void Sidebar::handleScaleChanged()
{
   Vector scale = Vector(xScale_->value(),
                         yScale_->value(),
                         zScale_->value());

   scale = scale * uScale_->value();

   options_.setScale(scale);
}

/**
 ******************************************************************************
 *
 *                   Show Normals
 *
 ******************************************************************************
 */
void Sidebar::handleShowNormalsChanged()
{
   options_.setDisplayNormals(ui_->showNormals->isChecked());
}

/**
 ******************************************************************************
 *
 *                   Select Model
 *
 ******************************************************************************
 */
void Sidebar::handleModelSelected()
{
   // Browse if that's selected
   if (ui_->selectModel->currentText() == QString("Browse..."))
   {
      // Show the open file dialog
      QString path = QFileDialog::getOpenFileName(this, 
                                                  "Select Model...",
                                                  ".",
                                                  "MD2 Models (*.md2)");

      // Load model if something was selected
      if (path != "")
      {
         modelSelector_.loadCustomModel(path);
      }

      return;
   }

   // Otherwise, load a preset model set
   modelSelector_.loadModelSet(ui_->selectModel->currentText());
}

/**
 ******************************************************************************
 *
 *                   Projection Mode
 *
 ******************************************************************************
 */
void Sidebar::handleProjectionChanged()
{
   ProjectionMode mode = (ui_->perspective->isChecked() ? Perspective
                                                        : Parallel);

   options_.setProjectionMode(mode);
}

/**
 ******************************************************************************
 *
 *                   Eye Position
 *
 ******************************************************************************
 */
void Sidebar::handleEyePositionChanged()
{
   Vector position = Vector(xView_->value(),
                            yView_->value(),
                            zView_->value());

   options_.setEyePosition(position);
}

/**
 ******************************************************************************
 *
 *                   Look-At Position
 *
 ******************************************************************************
 */
void Sidebar::handleLookAtPositionChanged()
{
   Vector position = Vector(xLookAt_->value(),
                            yLookAt_->value(),
                            zLookAt_->value());

   options_.setLookAtPosition(position);
}

/**
 ******************************************************************************
 *
 *                   Up Direction
 *
 ******************************************************************************
 */
void Sidebar::handleUpDirectionChanged()
{
   Vector direction = Vector(xUp_->value(),
                             yUp_->value(),
                             zUp_->value());

   options_.setUpDirection(direction);
}


/**
 ******************************************************************************
 *
 *                   Handle RenderOptions changing from external source
 *                   (e.g. mouse or auto-centering)
 *
 ******************************************************************************
 */
void Sidebar::handleEyePositionChangedByRenderOptions()
{
   Vector position = options_.eyePosition();

   xView_->setValue(position.x);
   yView_->setValue(position.y);
   zView_->setValue(position.z);
}

void Sidebar::handleLookAtPositionChangedByRenderOptions()
{
   Vector position = options_.lookAtPosition();

   xLookAt_->setValue(position.x);
   yLookAt_->setValue(position.y);
   zLookAt_->setValue(position.z);
}

