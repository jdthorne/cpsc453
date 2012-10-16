
// System

// Qt
#include <QVBoxLayout>
#include <QRadioButton>
#include <QGroupBox>

// UIC
#include <SidebarUi.ui.h>

// Project
#include <Vector.h>
#include <Sidebar.h>
#include <RenderHelpers.h>
#include <I_RenderOptions.h>
#include <I_ModelSelector.h>

using namespace RenderHelpers;

Sidebar::Sidebar(I_RenderOptions& options, I_ModelSelector& modelSelector)
   : options_(options)
   , modelSelector_(modelSelector)
{
   ui_ = new Ui_SidebarUi();
   ui_->setupUi(this);
   setMinimumWidth(260);

   // Input Controls
   setupInput(ui_->xTranslation, ui_->xTranslationSpin, SLOT(handleTranslationChanged()));
   setupInput(ui_->yTranslation, ui_->yTranslationSpin, SLOT(handleTranslationChanged()));
   setupInput(ui_->zTranslation, ui_->zTranslationSpin, SLOT(handleTranslationChanged()));

   setupInput(ui_->xScale, ui_->xScaleSpin, SLOT(handleScaleChanged()));
   setupInput(ui_->yScale, ui_->yScaleSpin, SLOT(handleScaleChanged()));
   setupInput(ui_->zScale, ui_->zScaleSpin, SLOT(handleScaleChanged()));
   setupInput(ui_->uScale, ui_->uScaleSpin, SLOT(handleScaleChanged()));

   setupInput(ui_->rRotation, ui_->rRotationSpin, SLOT(handleRotationChanged()));
   setupInput(ui_->pRotation, ui_->pRotationSpin, SLOT(handleRotationChanged()));
   setupInput(ui_->yRotation, ui_->yRotationSpin, SLOT(handleRotationChanged()));

   connect(ui_->showNormals, SIGNAL(toggled(bool)), this, SLOT(handleShowNormalsChanged()));

   connect(ui_->wireframe, SIGNAL(toggled(bool)), this, SLOT(handleRenderModeChanged()));
   connect(ui_->flat, SIGNAL(toggled(bool)), this, SLOT(handleRenderModeChanged()));
   connect(ui_->smooth, SIGNAL(toggled(bool)), this, SLOT(handleRenderModeChanged()));

   connect(ui_->perspective, SIGNAL(toggled(bool)), this, SLOT(handleProjectionChanged()));
   connect(ui_->parallel, SIGNAL(toggled(bool)), this, SLOT(handleProjectionChanged()));

   foreach(QString modelSet, modelSelector_.availableModelSets())
   {
      ui_->selectModel->addItem(modelSet);
   }
   ui_->selectModel->setCurrentIndex(modelSelector_.availableModelSets().count() - 1);
   connect(ui_->selectModel, SIGNAL(currentIndexChanged(int)), this, SLOT(handleModelSelected()));

   // Render Options
   connect(&options_, SIGNAL(rotationChanged()), this, SLOT(handleRotationChangedByRenderOptions()));
}

void Sidebar::setupInput(QAbstractSlider* slider, QSpinBox* spin, const char* slotToCallOnChange)
{
   spin->setMaximum(slider->maximum());
   spin->setMinimum(slider->minimum());
   spin->setValue(slider->value());

   connect(slider, SIGNAL(valueChanged(int)), spin, SLOT(setValue(int)));
   connect(spin, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));

   connect(slider, SIGNAL(valueChanged(int)), this, slotToCallOnChange);
   connect(spin, SIGNAL(valueChanged(int)), this, slotToCallOnChange);
}

Sidebar::~Sidebar()
{
}

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

void Sidebar::handleTranslationChanged()
{
   Vector translation = Vector(ui_->xTranslation->value(),
                               ui_->yTranslation->value(),
                               ui_->zTranslation->value());

   options_.setTranslation(translation);
}

void Sidebar::handleScaleChanged()
{
   Vector scale = Vector(ui_->xScale->value(),
                         ui_->yScale->value(),
                         ui_->zScale->value());

   scale = scale * ui_->uScale->value();

   options_.setScale(scale);
}

void Sidebar::handleRotationChanged()
{
   Euler rotation = Euler(toRad(ui_->rRotation->value()), 
                          toRad(ui_->pRotation->value()),
                          toRad(ui_->yRotation->value()));

   options_.setRotation(rotation);
}

void Sidebar::handleShowNormalsChanged()
{
   options_.setDisplayNormals(ui_->showNormals->isChecked());
}

void Sidebar::handleModelSelected()
{
   modelSelector_.loadModelSet(ui_->selectModel->currentText());
}

void Sidebar::handleProjectionChanged()
{
   ProjectionMode mode = (ui_->perspective->isChecked() ? Perspective
                                                        : Parallel);

   options_.setProjectionMode(mode);
}

/**
 ******************************************************************************
 *
 *                   Handle RenderOptions changing from external source
 *                   (e.g. mouse)
 *
 ******************************************************************************
 */
void Sidebar::handleRotationChangedByRenderOptions()
{
   Euler rotation = options_.rotation();

   ui_->rRotation->setValue(toDeg(rotation.roll));
   ui_->pRotation->setValue(toDeg(rotation.pitch));
   ui_->yRotation->setValue(toDeg(rotation.yaw));

   ui_->rRotationSpin->setValue(toDeg(rotation.roll));
   ui_->pRotationSpin->setValue(toDeg(rotation.pitch));
   ui_->yRotationSpin->setValue(toDeg(rotation.yaw));
}

