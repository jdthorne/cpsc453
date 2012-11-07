
#include <AssignmentCore.h>
#include <QApplication>

/**
 ******************************************************************************
 *
 *                   Main Initialization Function
 *
 ******************************************************************************
 */
int main(int argc, char** argv)
{
   // Make a QApplication
   QApplication app(argc, argv);

   // Make an AssignmentCore
   AssignmentCore core;
   core.show();

   // Execute the app
   return app.exec();
}
