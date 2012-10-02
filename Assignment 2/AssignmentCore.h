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
