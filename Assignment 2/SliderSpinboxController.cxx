
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
   slider->setMinimum(min_ * SLIDER_RESOLUTION);
   slider->setMaximum(max_ * SLIDER_RESOLUTION);

   spinBox->setMinimum(min_);
   spinBox->setMaximum(max_);

   setValue(value_);

   connect(slider, SIGNAL(valueChanged(int)), this, SLOT(handleSliderChanged()));
   connect(spinBox, SIGNAL(valueChanged(double)), this, SLOT(handleSpinBoxChanged()));

   connect(this, SIGNAL(valueChanged()), owner, slotToCall);
}

SliderSpinboxController::~SliderSpinboxController()
{
}

double SliderSpinboxController::value()
{
   return value_;
}

void SliderSpinboxController::setValue(double value)
{
   value_ = value;

   slider_->blockSignals(true);
   spinBox_->blockSignals(true);

   slider_->setValue(value * SLIDER_RESOLUTION);
   spinBox_->setValue(value);

   slider_->blockSignals(false);
   spinBox_->blockSignals(false);
}

void SliderSpinboxController::handleSliderChanged()
{
   setValue(slider_->value() / SLIDER_RESOLUTION);
   emit valueChanged();
}

void SliderSpinboxController::handleSpinBoxChanged()
{
   setValue(spinBox_->value());
   emit valueChanged();
}

