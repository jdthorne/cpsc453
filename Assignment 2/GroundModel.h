#ifndef GROUNDMODEL_H
#define GROUNDMODEL_H

// System

// Project
#include <OpenGlTexture.h>
#include <Model.h>

/**
 ******************************************************************************
 *
 *                   GroundModel
 *
 *  This class is a subclass of "Model" that represents the ground plate
 *  (i.e. the big gear thing).
 *
 ******************************************************************************
 */
class GroundModel : public Model
{

public:
   GroundModel();
   ~GroundModel();

   void setZPosition(double z);

public: // render functions
   virtual void renderMesh();
   virtual void renderNormals();

public: // accessors
   virtual Vector center();
   virtual Vector size();

private: // members
   OpenGlTexture texture_;
   double zPosition_;
};

#endif
