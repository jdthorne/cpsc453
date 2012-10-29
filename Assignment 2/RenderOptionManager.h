#ifndef RENDEROPTIONMANAGER_H
#define RENDEROPTIONMANAGER_H

// System

// Project
#include <I_RenderOptions.h>

/**
 ******************************************************************************
 *
 *                   RenderOptionManager
 *
 * This class "glues" multiple ModelRenderers together, so they can be controlled
 * from a central interface.
 *
 * This class also separates out a primary render options class, which is the
 * sole class that receives eye position changes.
 *
 ******************************************************************************
 */
class RenderOptionManager : public I_RenderOptions
{
   Q_OBJECT

public:
   RenderOptionManager(I_RenderOptions* primaryRenderOptions,
                       QList<I_RenderOptions*> secondaryRenderOptions_);
   virtual ~RenderOptionManager();

public: // I_RenderOptions

   // Accessors
   virtual AffineMatrix rotation();
   virtual Vector eyePosition();
   virtual Vector lookAtPosition();

   // Setters
   virtual void setRenderMode(RenderMode mode);
   virtual void setAlternativeMode(AlternativeMode mode);
   virtual void setTranslation(Vector translation);
   virtual void setRotation(AffineMatrix rotation);
   virtual void setScale(Vector scale);
   virtual void setDisplayNormals(bool displayNormals);
   virtual void setProjectionMode(ProjectionMode mode);

   virtual void setEyePosition(Vector position);
   virtual void setLookAtPosition(Vector position);
   virtual void setUpDirection(Vector direction);

   // Other functions
   virtual void forceRedraw();

signals:
   void rotationChanged();

   void eyePositionChanged();
   void lookAtPositionChanged();

private: // helpers

private: // members
   I_RenderOptions* primaryOptions_;
   QList<I_RenderOptions*> secondaryOptions_;

   QList<I_RenderOptions*> allRenderOptions_;
};

#endif
