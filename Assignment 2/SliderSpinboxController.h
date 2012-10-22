#ifndef SLIDERSPINBOXCONTROLLER_H
#define SLIDERSPINBOXCONTROLLER_H

// System

// Qt
#include <QObject>
#include <QSlider>
#include <QDoubleSpinBox>

// Project

/**
 ******************************************************************************
 *
 *                   SliderSpinboxController
 *
 ******************************************************************************
 */
class SliderSpinboxController : public QObject
{
   Q_OBJECT

public:
   SliderSpinboxController(QSlider* slider, QDoubleSpinBox* spinBox, 
                           QObject* owner, const char* slotToCall);
   virtual ~SliderSpinboxController();

public:
   double value();

public slots:
   void setValue(double value);

signals:
   void valueChanged();

private slots:
   void handleSliderChanged();
   void handleSpinBoxChanged();

private: // members
   QSlider* slider_;
   QDoubleSpinBox* spinBox_;

   QObject* owner_;
   const char* slotToCall_;

   double min_;
   double max_;
   double value_;
};

#endif
