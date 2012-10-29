
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

/**
 ******************************************************************************
 *
 *                   Accessors (from primary render options)
 *
 ******************************************************************************
 */
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

/**
 ******************************************************************************
 *
 *                   Simple wiring functions
 *
 ******************************************************************************
 */
#define CALL_ON_ALL_MANAGED_RENDER_OPTIONS(function, parameterType, parameterName) \
   void RenderOptionManager::function(parameterType parameterName) \
   { \
      foreach(I_RenderOptions* options, allRenderOptions_) \
      { \
         options->function(parameterName); \
      } \
   }

CALL_ON_ALL_MANAGED_RENDER_OPTIONS(setRenderMode, RenderMode, mode)
CALL_ON_ALL_MANAGED_RENDER_OPTIONS(setAlternativeMode, AlternativeMode, mode);
CALL_ON_ALL_MANAGED_RENDER_OPTIONS(setTranslation, Vector, translation);   
CALL_ON_ALL_MANAGED_RENDER_OPTIONS(setRotation, AffineMatrix, rotation);
CALL_ON_ALL_MANAGED_RENDER_OPTIONS(setScale, Vector, scale);
CALL_ON_ALL_MANAGED_RENDER_OPTIONS(setDisplayNormals, bool, displayNormals);
CALL_ON_ALL_MANAGED_RENDER_OPTIONS(setProjectionMode, ProjectionMode, mode);

/**
 ******************************************************************************
 *
 *                   Setup camera position (only on primary options)
 *
 ******************************************************************************
 */
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

/**
 ******************************************************************************
 *
 *                   Force redraw on all managed options
 *
 ******************************************************************************
 */
void RenderOptionManager::forceRedraw()
{
   foreach(I_RenderOptions* options, allRenderOptions_)
   {
      options->forceRedraw(); 
   }
}
