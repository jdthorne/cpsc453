
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
   this->setWindowTitle("CPSC453 Assignment 2 - MD2 Model Viewer - James Thorne");
   this->setMinimumSize(1280, 720);

   QWidget* centralWidget = new QWidget(this);

   QHBoxLayout* layout = new QHBoxLayout(centralWidget);
   centralWidget->setLayout(layout);

   openGlCore_ = new OpenGlCore();
   layout->addWidget(openGlCore_);

   sidebar_ = new Sidebar(openGlCore_->renderOptions());
   layout->addWidget(sidebar_);

   layout->setStretch(0, 1);
   layout->setStretch(1, 0);
   this->setCentralWidget(centralWidget);
}

AssignmentCore::~AssignmentCore()
{
}

void AssignmentCore::show()
{
   QMainWindow::show();
}
