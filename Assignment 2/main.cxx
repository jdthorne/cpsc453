
#include <AssignmentCore.h>
#include <QApplication>

/**
 ******************************************************************************
 *
 *                   Main Initialization
 *
 ******************************************************************************
 */
int main(int argc, char** argv)
{
   QApplication app(argc, argv);

   AssignmentCore core;
   core.show();

   return app.exec();
}
