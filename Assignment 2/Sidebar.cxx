
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
#include <I_RenderOptions.h>

Sidebar::Sidebar(I_RenderOptions& options)
   : options_(options)
{
   ui_ = new Ui_SidebarUi();
   ui_->setupUi(this);

   connect(ui_->xTranslation, SIGNAL(valueChanged(int)), this, SLOT(handleTranslationChanged()));
   connect(ui_->yTranslation, SIGNAL(valueChanged(int)), this, SLOT(handleTranslationChanged()));
   connect(ui_->zTranslation, SIGNAL(valueChanged(int)), this, SLOT(handleTranslationChanged()));

   connect(ui_->showNormals, SIGNAL(toggled(bool)), this, SLOT(handleShowNormalsChanged()));

   connect(ui_->wireframe, SIGNAL(toggled(bool)), this, SLOT(handleRenderModeChanged()));
   connect(ui_->flat, SIGNAL(toggled(bool)), this, SLOT(handleRenderModeChanged()));
   connect(ui_->smooth, SIGNAL(toggled(bool)), this, SLOT(handleRenderModeChanged()));
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

void Sidebar::handleShowNormalsChanged()
{
   options_.setDisplayNormals(ui_->showNormals->isChecked());
}

