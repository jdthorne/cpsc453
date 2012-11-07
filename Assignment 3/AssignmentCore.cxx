
// System

// Project
#include <AssignmentCore.h>

AssignmentCore::AssignmentCore()
{
   window_.setWindowTitle("Assignment 3 - Raytracer - James Thorne");

   imageViewer_ = new QLabel(&window_);
   imageViewer_->setMinimumSize(640, 360);

   window_.setCentralWidget(imageViewer_);
}

AssignmentCore::~AssignmentCore()
{
}

void AssignmentCore::show()
{
   window_.show();
}

