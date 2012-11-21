#ifndef ASSIGNMENTCORE_H
#define ASSIGNMENTCORE_H

// System

// Qt
#include <QMainWindow>
#include <QLabel>
#include <QComboBox>

// Project

/**
 ******************************************************************************
 *
 *                   AssignmentCore
 *
 * This class represents the main window, and handles user interaction
 *
 ******************************************************************************
 */
class AssignmentCore : public QMainWindow
{
   Q_OBJECT

public:
   AssignmentCore();
   virtual ~AssignmentCore();

private slots:
   virtual void handleRenderClicked();
   virtual void handleSaveClicked();

private: // helpers

private: // members
   QLabel* imageViewer_;
   QComboBox* sceneList_;
   QImage lastImage_;
};

#endif
