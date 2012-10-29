
// System

// Project
#include <RenderOptionManager.h>

RenderOptionManager::RenderOptionManager(I_RenderOptions* primaryRenderOptions,
                                         QList<I_RenderOptions*> secondaryRenderOptions)
   : primaryOptions_(primaryRenderOptions)
   , secondaryOptions_(secondaryRenderOptions)
{
   // Group everything together to make life easier
   allRenderOptions_.append(primaryOptions_);
   allRenderOptions_.append(secondaryOptions_);

   // Ensure we pass signals from the primary render options
   connect(primaryOptions_, SIGNAL(rotationChanged()), this, SIGNAL(rotationChanged()));
   connect(primaryOptions_, SIGNAL(eyePositionChanged()), this, SIGNAL(eyePositionChanged()));
   connect(primaryOptions_, SIGNAL(lookAtPositionChanged()), this, SIGNAL(lookAtPositionChanged()));
}

RenderOptionManager::~RenderOptionManager()
{
}

#define CALL_ON_ALL_MANAGED_RENDER_OPTIONS(function, parameter) \
   foreach(I_RenderOptions* options, allRenderOptions_) \
   { \
      options->function(parameter); \
   }

// Accessors
AffineMatrix RenderOptionManager::rotation()
{
   return primaryOptions_->rotation();
}

Vector RenderOptionManager::eyePosition()
{
   return primaryOptions_->eyePosition();
}

Vector RenderOptionManager::lookAtPosition()
{
   return primaryOptions_->lookAtPosition();
}

// Setters
void RenderOptionManager::setRenderMode(RenderMode mode)
{
   CALL_ON_ALL_MANAGED_RENDER_OPTIONS(setRenderMode, mode);
}

void RenderOptionManager::setAlternativeMode(AlternativeMode mode)
{
   CALL_ON_ALL_MANAGED_RENDER_OPTIONS(setAlternativeMode, mode);
}

void RenderOptionManager::setTranslation(Vector translation)
{
   CALL_ON_ALL_MANAGED_RENDER_OPTIONS(setTranslation, translation);   
}

void RenderOptionManager::setRotation(AffineMatrix rotation)
{
   CALL_ON_ALL_MANAGED_RENDER_OPTIONS(setRotation, rotation);
}

void RenderOptionManager::setScale(Vector scale)
{
   CALL_ON_ALL_MANAGED_RENDER_OPTIONS(setScale, scale);
}

void RenderOptionManager::setDisplayNormals(bool displayNormals)
{
   CALL_ON_ALL_MANAGED_RENDER_OPTIONS(setDisplayNormals, displayNormals);
}

void RenderOptionManager::setProjectionMode(ProjectionMode mode)
{
   CALL_ON_ALL_MANAGED_RENDER_OPTIONS(setProjectionMode, mode);
}


void RenderOptionManager::setEyePosition(Vector position)
{
   primaryOptions_->setEyePosition(position);
}

void RenderOptionManager::setLookAtPosition(Vector position)
{
   primaryOptions_->setLookAtPosition(position);
}

void RenderOptionManager::setUpDirection(Vector direction)
{
   primaryOptions_->setUpDirection(direction);
}

// Other functions
void RenderOptionManager::forceRedraw()
{
   foreach(I_RenderOptions* options, allRenderOptions_)
   {
      options->forceRedraw(); 
   }
}
