
// System

// Qt
#include <QDir>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCoreApplication>
#include <QFileDialog>

// Project
#include <Raytracer.h>
#include <AssignmentCore.h>

AssignmentCore::AssignmentCore()
{
   setWindowTitle("Assignment 3 - Raytracer - James Thorne");

   // Create the various widgets
   QWidget* mainWidget = new QWidget();
   QWidget* menuBar = new QWidget();

   imageViewer_ = new QLabel(this);
   imageViewer_->setMinimumSize(640, 360);

   // Make the vertical layout
   QVBoxLayout* vLayout = new QVBoxLayout(mainWidget);
   mainWidget->setLayout(vLayout);
   vLayout->addWidget(menuBar);
   vLayout->addWidget(imageViewer_);
   vLayout->setStretch(0, 0);   
   vLayout->setStretch(1, 1);   
   vLayout->setMargin(0);
   vLayout->setSpacing(0);

   sceneList_ = new QComboBox(menuBar);

   // Make the "render" button
   QPushButton* renderButton = new QPushButton(menuBar);
   renderButton->setText("Render");
   connect(renderButton, SIGNAL(clicked()), this, SLOT(handleRenderClicked()));

   // Make the "save" button
   QPushButton* saveButton = new QPushButton(menuBar);
   saveButton->setText("Save Image...");
   connect(saveButton, SIGNAL(clicked()), this, SLOT(handleSaveClicked()));

   // Make the horizontal layout
   QHBoxLayout* hLayout = new QHBoxLayout(menuBar);
   menuBar->setLayout(hLayout);
   hLayout->addWidget(sceneList_);
   hLayout->addWidget(renderButton);
   hLayout->addWidget(saveButton);
   hLayout->setStretch(0, 1);
   hLayout->setStretch(1, 0);
   hLayout->setStretch(2, 0);
   hLayout->setMargin(0);
   hLayout->setSpacing(5);

   this->setCentralWidget(mainWidget);

   // Load the list of scenes
   QDir sceneFolder = QDir(".");
   foreach(QString entry, sceneFolder.entryList())
   {
      if (entry.endsWith(".scene"))
      {
         sceneList_->addItem(entry);
      }  
   }

   // Make window non-resizable
   this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

AssignmentCore::~AssignmentCore()
{
}

/**
 ******************************************************************************
 *
 *                   Handle "render" button
 *
 ******************************************************************************
 */
void AssignmentCore::handleRenderClicked()
{
   // Load the selected scene
   QString currentScene = sceneList_->currentText();
   Scene scene(currentScene);

   // Make the raytracer
   Raytracer ray(scene);

   // Run the raytracer
   while (ray.running())
   {  
      // Run the raytracer for one cycle, grabbing the image
      QImage renderedImage = ray.run();
      lastImage_ = renderedImage;

      // Display the image
      imageViewer_->setPixmap(QPixmap::fromImage(renderedImage));

      // Update the screen
      QCoreApplication::processEvents();
   }
}

/**
 ******************************************************************************
 *
 *                   Handle the "save" button being clicked
 *
 ******************************************************************************
 */
void AssignmentCore::handleSaveClicked()
{
   // Show a save dialog
   QString filename = QFileDialog::getSaveFileName(this, "Save Rendered Image", ".", "PNG Image (*.png)");

   // Don't save if they say cancel
   if (filename == "")
   {
      return;
   }

   // Save the image
   qDebug("Saving rendered image to %s...", qPrintable(filename));
   lastImage_.save(filename);
}

