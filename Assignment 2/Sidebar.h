#ifndef SIDEBAR_H
#define SIDEBAR_H

// System
#include <QWidget>

// Project

class I_RenderOptions;
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
   Sidebar(I_RenderOptions& options);
   ~Sidebar();

public:

protected slots:
   void handleRenderModeChanged();
   void handleTranslationChanged();
   void handleShowNormalsChanged();

private: // helpers

private: // members
   Ui_SidebarUi* ui_;

   I_RenderOptions& options_;
};

#endif
