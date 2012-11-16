
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

   // Ensure command line parameters are OK
   if (argc != 2)
   {
      qDebug("Usage: %s [scene file]", argv[0]);
      return -1;
   }

   // Make an AssignmentCore
   AssignmentCore core;
   core.show();

   // Execute the app
   return app.exec();
}
