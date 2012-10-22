#ifndef SIDEBAR_H
#define SIDEBAR_H

// System
#include <QWidget>

// Project
#include <SliderSpinboxController.h>

class QSpinBox;
class QAbstractSlider;

class I_RenderOptions;
class I_ModelSelector;
class Ui_SidebarUi;

/**
 ******************************************************************************
 *
 *                   Sidebar
 *
 ******************************************************************************
 */
class Sidebar : public QWidget
{
   Q_OBJECT
   
public:
   Sidebar(I_RenderOptions& options, I_ModelSelector& modelManager);
   ~Sidebar();

public:

protected slots: // Sidebar Interface Changes
   void handleRenderModeChanged();
   void handleTranslationChanged();
   void handleScaleChanged();
   void handleRotationChanged();
   void handleShowNormalsChanged();
   void handleProjectionChanged();

   void handleEyePositionChanged();
   void handleLookAtPositionChanged();
   void handleUpDirectionChanged();

   void handleModelSelected();

protected slots: // Render Option Changes
   void handleRotationChangedByRenderOptions();
   void handleEyePositionChangedByRenderOptions();
   void handleLookAtPositionChangedByRenderOptions();

private: // helpers
   void setupInput(QAbstractSlider* slider, QSpinBox* spin, const char* slotToCallOnChange);

private: // members
   Ui_SidebarUi* ui_;

   I_RenderOptions& options_;
   I_ModelSelector& modelSelector_;

private: // controllers
   SliderSpinboxController* xTranslation_;
   SliderSpinboxController* yTranslation_;
   SliderSpinboxController* zTranslation_;

   SliderSpinboxController* xScale_;
   SliderSpinboxController* yScale_;
   SliderSpinboxController* zScale_;
   SliderSpinboxController* uScale_;

   SliderSpinboxController* rRotation_;
   SliderSpinboxController* pRotation_;
   SliderSpinboxController* yRotation_;

   SliderSpinboxController* xView_;
   SliderSpinboxController* yView_;
   SliderSpinboxController* zView_;

   SliderSpinboxController* xLookAt_;
   SliderSpinboxController* yLookAt_;
   SliderSpinboxController* zLookAt_;

   SliderSpinboxController* xUp_;
   SliderSpinboxController* yUp_;
   SliderSpinboxController* zUp_;

};

#endif
