#ifndef SIDEBAR_H
#define SIDEBAR_H

// System
#include <QWidget>

// Project
#include <SliderSpinboxController.h>

class QSpinBox;
class QAbstractSlider;
class QLabel;

class I_RenderOptions;
class I_ModelSelector;
class Ui_SidebarUi;

/**
 ******************************************************************************
 *
 *                   Sidebar
 *
 *  This class owns all of the widgets in the sidebar, and wires then up to
 *  I_RenderOptions and I_ModelManager.
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
   void handleShowNormalsChanged();
   void handleProjectionChanged();
   void handleUseHandWrittenChanged();

   void handleEyePositionChanged();
   void handleLookAtPositionChanged();
   void handleUpDirectionChanged();

   void handleModelSelected();

   void handleBrowseForModel();
   void handleBrowseForModelSkin();
   void handleBrowseForWeapon();
   void handleBrowseForWeaponSkin();

protected slots: // Render Option Changes
   void handleEyePositionChangedByRenderOptions();
   void handleLookAtPositionChangedByRenderOptions();

private: // helpers
   void setupInput(QAbstractSlider* slider, QSpinBox* spin, const char* slotToCallOnChange);

   void loadCustomModel();
   void setTextWithEllipsis(QLabel* label, QString text);

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

   SliderSpinboxController* xView_;
   SliderSpinboxController* yView_;
   SliderSpinboxController* zView_;

   SliderSpinboxController* xLookAt_;
   SliderSpinboxController* yLookAt_;
   SliderSpinboxController* zLookAt_;

   SliderSpinboxController* xUp_;
   SliderSpinboxController* yUp_;
   SliderSpinboxController* zUp_;

   QString modelPath_;
   QString modelSkinPath_;
   QString weaponPath_;
   QString weaponSkinPath_;

};

#endif
