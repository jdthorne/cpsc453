
// System
#include <stdio.h>

// Qt
#include <QHBoxLayout>

// Project
#include <AssignmentCore.h>
#include <OpenGlCore.h>
#include <Sidebar.h>

AssignmentCore::AssignmentCore()
{
   // Setup the window frame
   this->setWindowTitle("CPSC453 Assignment 2 - MD2 Model Viewer - James Thorne");
   this->resize(1280, 720);

   // Create a central widget
   QWidget* centralWidget = new QWidget(this);

   // Create a layout
   QHBoxLayout* layout = new QHBoxLayout(centralWidget);
   centralWidget->setLayout(layout);

   // Create the OpenGL core
   openGlCore_ = new OpenGlCore();
   layout->addWidget(openGlCore_);

   // Create the sidebar
   sidebar_ = new Sidebar(openGlCore_->renderOptions(), openGlCore_->modelSelector());
   layout->addWidget(sidebar_);

   // Configure the layout
   layout->setStretch(0, 1);
   layout->setStretch(1, 0);

   // Add the central widget
   this->setCentralWidget(centralWidget);
}

AssignmentCore::~AssignmentCore()
{
}

/**
 ******************************************************************************
 *
 *                   Show the main window
 *
 ******************************************************************************
 */
void AssignmentCore::show()
{
   QMainWindow::show();
}
