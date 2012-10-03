#ifndef MODEL_H
#define MODEL_H

// Qt
#include <QMap>

// System

// Project
#include <Vector.h>

/**
 ******************************************************************************
 *
 *                   Model
 *
 ******************************************************************************
 */
class Model
{
public:
   Model();
   virtual ~Model();

public: // render functions
   virtual void renderMesh() = 0;
   virtual void renderNormals() = 0;

public: // accessors
   virtual Vector center() = 0;
   virtual Vector size() = 0;
};

#endif
