#ifndef I_RENDEROPTIONS_H
#define I_RENDEROPTIONS_H

// System

// Qt
#include <QObject>

// Project
#include <Vector.h>
#include <Euler.h>

enum RenderMode
{
   Wireframe,
   FlatShading,
   SmoothShading
};

enum ProjectionMode
{
   Perspective,
   Parallel
};

/**
 ******************************************************************************
 *
 *                   I_RenderOptions
 *
 ******************************************************************************
 */
class I_RenderOptions : public QObject
{

public:
   virtual ~I_RenderOptions() {};

public:
   // Accessors
   virtual Euler rotation() = 0;

/*   virtual Vector eyePosition() = 0;
   virtual Vector lookAtPosition() = 0;
   virtual Vector upDirection() = 0;
*/
   // Setters
   virtual void setRenderMode(RenderMode mode) = 0;
   virtual void setTranslation(Vector translation) = 0;
   virtual void setRotation(Euler rotation) = 0;
   virtual void setScale(Vector scale) = 0;
   virtual void setDisplayNormals(bool displayNormals) = 0;
   virtual void setProjectionMode(ProjectionMode mode) = 0;

/*   virtual void setEyePosition(Vector position) = 0;
   virtual void setLookAtPosition(Vector position) = 0;
   virtual void setUpDirection(Vector direction) = 0;
*/
public: // signals
   virtual void rotationChanged() = 0;

/*   virtual void eyePositionChanged() = 0;
   virtual void lookAtPositionChanged() = 0;
   virtual void upDirectionChanged() = 0;
*/
};

#endif
