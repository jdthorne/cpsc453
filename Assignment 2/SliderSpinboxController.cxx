
// System

// Project
#include <SliderSpinboxController.h>

const double SLIDER_RESOLUTION = 100;

SliderSpinboxController::SliderSpinboxController(QSlider* slider, QDoubleSpinBox* spinBox,
                                                 QObject* owner, const char* slotToCall)
   : slider_(slider)
   , spinBox_(spinBox)
   , owner_(owner)
   , slotToCall_(slotToCall)
   , min_(slider->minimum())
   , max_(slider->maximum())
   , value_(slider->value())
{

   // Multiply everything in the slider by SLIDER_RESOLUTION to simulate
   // a floating-point slider (i.e. allow changes of 0.01 instead of 1)
   slider->setMinimum(min_ * SLIDER_RESOLUTION);
   slider->setMaximum(max_ * SLIDER_RESOLUTION);

   // Configure the spinbox to match the slider
   spinBox->setMinimum(min_);
   spinBox->setMaximum(max_);

   // Make sure everything has the same value on startup
   setValue(value_);

   // Wire up changes
   connect(slider, SIGNAL(valueChanged(int)), this, SLOT(handleSliderChanged()));
   connect(spinBox, SIGNAL(valueChanged(double)), this, SLOT(handleSpinBoxChanged()));

   // Make sure we notify our owner if we change
   connect(this, SIGNAL(valueChanged()), owner, slotToCall);
}

SliderSpinboxController::~SliderSpinboxController()
{
}

/**
 ******************************************************************************
 *
 *                   Retrieve the current value
 *
 ******************************************************************************
 */
double SliderSpinboxController::value()
{
   return value_;
}

/**
 ******************************************************************************
 *
 *                   Set the current value
 *
 ******************************************************************************
 */
void SliderSpinboxController::setValue(double value)
{
   // Save the value
   value_ = value;

   // Make sure we don't get into an infinite-signal loop
   slider_->blockSignals(true);
   spinBox_->blockSignals(true);

   // Set the value on both widgets
   slider_->setValue(value * SLIDER_RESOLUTION);
   spinBox_->setValue(value);

   // Make sure we do get signals when we're done
   slider_->blockSignals(false);
   spinBox_->blockSignals(false);
}

/**
 ******************************************************************************
 *
 *                   Handle slider changes
 *
 ******************************************************************************
 */
void SliderSpinboxController::handleSliderChanged()
{
   setValue(slider_->value() / SLIDER_RESOLUTION);
   emit valueChanged();
}

/**
 ******************************************************************************
 *
 *                   Handle spinbox changes
 *
 ******************************************************************************
 */
void SliderSpinboxController::handleSpinBoxChanged()
{
   setValue(spinBox_->value());
   emit valueChanged();
}

