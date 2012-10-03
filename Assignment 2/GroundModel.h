#ifndef GROUNDMODEL_H
#define GROUNDMODEL_H

// System

// Project
#include <Model.h>

/**
 ******************************************************************************
 *
 *                   GroundModel
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
   int textureName_;
   double zPosition_;
};

#endif
