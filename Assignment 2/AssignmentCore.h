#ifndef ASSIGNMENTCORE_H
#define ASSIGNMENTCORE_H

// System
#include <QMainWindow>

// Project
class OpenGlCore;
class Sidebar;

/**
 ******************************************************************************
 *
 *                   OpenGlDisplay
 *
 *  This class is the "main window" of Assignment 2.  It constructs the
 *  OpenGlCore and the Sidebar, and delegates the actual work to them.
 *
 ******************************************************************************
 */
class AssignmentCore : private QMainWindow
{ 
   Q_OBJECT

public:
   AssignmentCore();
   virtual ~AssignmentCore();

   void show();

private:
   OpenGlCore* openGlCore_;
   Sidebar* sidebar_;

};

#endif
