
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

   QWidget* mainWidget = new QWidget();
   QWidget* menuBar = new QWidget();

   imageViewer_ = new QLabel(this);
   imageViewer_->setMinimumSize(640, 360);

   QVBoxLayout* vLayout = new QVBoxLayout(mainWidget);
   mainWidget->setLayout(vLayout);
   vLayout->addWidget(menuBar);
   vLayout->addWidget(imageViewer_);
   vLayout->setStretch(0, 0);   
   vLayout->setStretch(1, 1);   
   vLayout->setMargin(0);
   vLayout->setSpacing(0);

   sceneList_ = new QComboBox(menuBar);

   QPushButton* renderButton = new QPushButton(menuBar);
   renderButton->setText("Render");
   connect(renderButton, SIGNAL(clicked()), this, SLOT(handleRenderClicked()));

   QPushButton* saveButton = new QPushButton(menuBar);
   saveButton->setText("Save Image...");
   connect(saveButton, SIGNAL(clicked()), this, SLOT(handleSaveClicked()));

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

   QDir sceneFolder = QDir(".");
   foreach(QString entry, sceneFolder.entryList())
   {
      if (entry.endsWith(".scene"))
      {
         sceneList_->addItem(entry);
      }  
   }

   this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

AssignmentCore::~AssignmentCore()
{
}

void AssignmentCore::handleRenderClicked()
{
   QString currentScene = sceneList_->currentText();
   Scene scene(currentScene);

   Raytracer ray(scene);

   while (ray.running())
   {
      QImage renderedImage = ray.run();
      lastImage_ = renderedImage;

      imageViewer_->setPixmap(QPixmap::fromImage(renderedImage));

      QCoreApplication::processEvents();
   }
}

void AssignmentCore::handleSaveClicked()
{
   QString filename = QFileDialog::getSaveFileName(this, "Save Rendered Image", ".", "PNG Image (*.png)");

   if (filename == "")
   {
      return;
   }

   qDebug("Saving rendered image to %s...", qPrintable(filename));
   lastImage_.save(filename);
}

