#ifndef ASSIGNMENTCORE_H
#define ASSIGNMENTCORE_H

// System

// Qt
#include <QMainWindow>
#include <QLabel>

// Project

/**
 ******************************************************************************
 *
 *                   AssignmentCore
 *
 ******************************************************************************
 */
class AssignmentCore
{

public:
   AssignmentCore();
   virtual ~AssignmentCore();

public:
   void show();

private: // helpers

private: // members
   QMainWindow window_;
   QLabel* imageViewer_;
};

#endif
