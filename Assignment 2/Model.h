#ifndef MODEL_H
#define MODEL_H

// Qt
#include <QMap>
#include <QObject>

// System

// Project
#include <I_RenderOptions.h>
#include <Vector.h>

/**
 ******************************************************************************
 *
 *                   Model
 *
 *  This is an abstract base class for models, which can be rendered and
 *  have bounds.
 *
 *  The two specializations are GroundModel, which is built on the fly, and
 *  Md2Model, which is loaded from a file.
 *
 ******************************************************************************
 */
class Model : public QObject
{
public:
   Model();
   virtual ~Model();

public: // render functions
   virtual void renderMesh(AlternativeMode mode) = 0;
   virtual void renderNormals() = 0;

   virtual void resetAnimation() = 0;

public: // accessors
   virtual Vector center() = 0;
   virtual Vector size() = 0;

public: // signals
   virtual void frameChanged() = 0;

};

#endif
