
// System

// Qt
#include <QImage>

// Project
#include <Md2Model.h>
#include <RenderHelpers.h>

using namespace RenderHelpers;

Md2Model::Md2Model(QString modelDataFilename, QString skinTextureFilename)
   : texture_(skinTextureFilename)
   , currentAnimation_(0)
   , currentFrame_(0)
{
   // Load the MD2 model
   data_ = new MD2();
   bool ok = data_->LoadModel(qPrintable(modelDataFilename));

   if (ok)
   {
      // Precalculate expensive things
      calculateBounds();
      calculateFaceNormals();
      calculateVertexNormals();

      // Start animating
      connect(&animationTimer_, SIGNAL(timeout()), this, SLOT(handleFrameTimeout()));
      animationTimer_.start(1000.0 / data_->animlist[currentAnimation_].fps); 
   }
}

Md2Model::~Md2Model()
{
   delete data_;
}

/**
 ******************************************************************************
 *
 *                   Render the actual mesh
 *
 ******************************************************************************
 */
void Md2Model::renderMesh(AlternativeMode mode)
{
   // Enable lighting
   glEnable(GL_LIGHTING);

   // Bind the texture
   glEnable(GL_TEXTURE_2D);
   texture_.bind();

   // Set up the normal rendering mode
   if (mode == NormalRender)
   {
      // Set the color to "white", so only the texture is used
      glColor3f(1, 1, 1);
   }

   // Otherwise, set up the alternate mode
   else if (mode == AlternativeRender)
   {
      // Use additive alpha blending
      glEnable(GL_BLEND);
      glBlendFunc(GL_ONE, GL_ONE);

      // Make the ghost blueish
      glColor3f(0.6, 0.7, 1.0);

      // Ensure all faces draw
      glDisable(GL_DEPTH_TEST);
   }

   // Start drawing triangles...
   glBegin(GL_TRIANGLES);
   for (int i = 0; i < data_->num_tris; i++)
   {
      // Grab the triangle
      triangle_t triangle = data_->tris[i];

      // Walk through the vertices
      for (int v = 0; v < 3; v++)
      {
         // Grab the IDs
         int vertexId = triangle.index_xyz[v];
         int texId = triangle.index_st[v];

         // Apply animation
         vertexId += (data_->num_xyz * currentFrame_);

         // Tell OpenGL the normal
         Vector normal = vertexNormals_[vertexId];
         jdNormalv(normal);

         // Tell OpenGL the texture coordinate (with a flipped y-coordinate)
         tex_coord& tex = data_->texs[texId];
         float uCoord = (float)tex.u / data_->skin_width;
         float vCoord = (data_->skin_height) - ((float)tex.v / data_->skin_height);
         glTexCoord2f(uCoord, vCoord);

         // Tell OpenGL the actual vertex
         Vector vertex = Vector(data_->m_vertices[vertexId]);
         jdVertexv(vertex);
      }
   }
   glEnd();

   // Disable the stuff we used
   glDisable(GL_TEXTURE_2D);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glDisable(GL_LIGHTING);
   glEnable(GL_DEPTH_TEST);
}

/**
 ******************************************************************************
 *
 *                   Render the model normals
 *
 ******************************************************************************
 */
void Md2Model::renderNormals()
{
   // Render the normals as lines
   glBegin(GL_LINES);

   // Draw the face normals in green
   glColor3f(0, 1, 0);
   for (int i = 0; i < data_->num_tris; i++)
   {
      // Find the center of the face
      Vector centerOfFace;
      for (int v = 0; v < 3; v++)
      {
         // Find Vertex Index
         int vertexId = data_->tris[i].index_xyz[v];

         // Apply animation
         vertexId += (data_->num_xyz * currentFrame_);

         // Add the vertex position to the center
         centerOfFace += Vector(data_->m_vertices[vertexId]) * (1.0 / 3.0);
      }

      // Find the center of the face and the normal
      Vector normal = faceNormals_[i] * 3;

      // Draw a line from (center) to (center + normal)
      jdVertexv(centerOfFace);
      jdVertexv(centerOfFace + normal);
   }

   // Draw the vertex normals in blue
   glColor3f(0, 0, 1);
   for (int i = 0; i < data_->num_xyz; i++)
   {
      // Find the animation offset
      int frameOffset = (data_->num_xyz * currentFrame_);

      // Find the vertex and its normal
      Vector vertex = Vector(data_->m_vertices[i + frameOffset]);
      Vector normal = vertexNormals_[i] * 3;

      // Draw a line from (vertex) to (vertex + normal)
      jdVertexv(vertex);
      jdVertexv(vertex + normal);
   }

   glEnd();
}

/**
 ******************************************************************************
 *
 *                   Calculate the bounding box
 *
 ******************************************************************************
 */
void Md2Model::calculateBounds()
{
   // Our goal is to find the max/min values
   double xMin = 0, yMin = 0, zMin = 0;
   double xMax = 0, yMax = 0, zMax = 0;
   
   // Loop through the vertices
   for (int i = 0; i < data_->num_xyz; i++)
   {
      // Grab the vertex
      Vector vertex = Vector(data_->m_vertices[i]);
      
      // Save the min/max values
      xMin = qMin(xMin, vertex.x);
      yMin = qMin(yMin, vertex.y);
      zMin = qMin(zMin, vertex.z);

      xMax = qMax(xMax, vertex.x);
      yMax = qMax(yMax, vertex.y);
      zMax = qMax(zMax, vertex.z);
   }

   // Find the actual min and max
   Vector minimum = Vector(xMin, yMin, zMin);
   Vector maximum = Vector(xMax, yMax, zMax);

   // Center = average of min+max, size = max - min
   center_ = (minimum + maximum) / 2.0;
   size_ = maximum - minimum;
}

/**
 ******************************************************************************
 *
 *                   Calculate the face normals
 *
 ******************************************************************************
 */
void Md2Model::calculateFaceNormals()
{
   // Loop through the verts...
   for (int i = 0; i < data_->num_tris; i++)
   {
      // Find the triangle
      const triangle_t& triangle = data_->tris[i];

      // Find the three vertices
      Vector vertex0 = Vector(data_->m_vertices[triangle.index_xyz[0]]);
      Vector vertex1 = Vector(data_->m_vertices[triangle.index_xyz[1]]);
      Vector vertex2 = Vector(data_->m_vertices[triangle.index_xyz[2]]);

      // Find lines from 0->1 and 0->2
      Vector line01 = vertex1 - vertex0;
      Vector line02 = vertex2 - vertex0;

      // Cross product the lines
      Vector normal = line02.cross(line01).normalized(); 

      // Save the calculated normal
      faceNormals_[i] = normal;
   }   
}

/**
 ******************************************************************************
 *
 *                   Calculate the vertex normals
 *
 ******************************************************************************
 */
void Md2Model::calculateVertexNormals()
{
   for (int vertexId = 0; vertexId < data_->num_xyz; vertexId++)
   {
      // Find the triangles that include this vertex
      QList<int> triangles;
      for (int triangleId = 0; triangleId < data_->num_tris; triangleId++)
      {
         // If the triangle uses this vertex, append it
         const triangle_t& triangle = data_->tris[triangleId];
         if (   triangle.index_xyz[0] == vertexId
             || triangle.index_xyz[1] == vertexId
             || triangle.index_xyz[2] == vertexId)
         {
            triangles.append(triangleId);
         }
      }

      // Average the normals of the involved faces
      Vector averageNormal = Vector(0, 0, 0);
      foreach (int triangleId, triangles)
      {
         averageNormal += faceNormals_[triangleId];
      }

      // Save the resulting normal
      vertexNormals_[vertexId] = averageNormal.normalized();
   }
}

/**
 ******************************************************************************
 *
 *                   Accessors
 *
 ******************************************************************************
 */
Vector Md2Model::center()
{
   return center_;
}

Vector Md2Model::size()
{
   return size_;
}


/**
 ******************************************************************************
 *
 *                   Advance to the next frame
 *
 ******************************************************************************
 */
void Md2Model::handleFrameTimeout()
{
   // Some models don't have animation data - don't try animating them!
   if (data_->num_frames == 1)
   {
      return;
   }

   // Advance to the next frame
   currentFrame_++;

   // Loop to the next animation if necessary
   if (currentFrame_ > data_->animlist[currentAnimation_].last_frame)
   {
      // Advance the animation
      currentAnimation_++;

      // Loop the animations if we're at the end
      if (currentAnimation_ >= MAX_ANIMATIONS)
      {
         currentAnimation_ = 0;
      }

      // Go to the first frame of the chosen animation
      currentFrame_ = data_->animlist[currentAnimation_].first_frame;

      // Set the correct framerate
      animationTimer_.setInterval(1000.0 / data_->animlist[currentAnimation_].fps);
   }

   emit frameChanged();
}
