
// System

// Qt
#include <QImage>

// Project
#include <Md2Model.h>
#include <RenderHelpers.h>

using namespace RenderHelpers;

Md2Model::Md2Model(QString modelDataFilename, QString skinTextureFilename)
   : texture_(skinTextureFilename)
{
   // Load the MD2 model
   data_ = new MD2();
   data_->LoadModel(qPrintable(modelDataFilename));

   // Precalculate expensive things
   calculateBounds();
   calculateFaceNormals();
   calculateVertexNormals();
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
void Md2Model::renderMesh()
{
   // Enable lighting
   glEnable(GL_LIGHTING);

   // Bind the texture
   glEnable(GL_TEXTURE_2D);
   texture_.bind();

   // Start drawing triangles...
   glColor3f(1, 1, 1);
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

         // Tell OpenGL the normal
         Vector normal = vertexNormals_[vertexId] * -1;
         jdNormalv(normal);

         // Tell OpenGL the texture coordinate
         tex_coord& tex = data_->texs[texId];
         glTexCoord2f((float)tex.u / data_->skin_width, (float)tex.v / data_->skin_height);

         // Tell OpenGL the actual vertex
         Vector vertex = Vector(data_->m_vertices[vertexId]);
         jdVertexv(vertex);
      }
   }
   glEnd();

   // Disable the stuff we used
   glDisable(GL_TEXTURE_2D);
   glDisable(GL_LIGHTING);
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
      // Find the center of the face and the normal
      Vector centerOfFace = faceCenters_[i];
      Vector normal = faceNormals_[i] * 3;

      // Draw a line from (center - normal) to (center + normal)
      jdVertexv(centerOfFace - normal);
      jdVertexv(centerOfFace + normal);
   }

   // Draw the vertex normals in blue
   glColor3f(0, 0, 1);
   for (int i = 0; i < data_->num_xyz; i++)
   {
      // Find the vertex and its normal
      Vector vertex = Vector(data_->m_vertices[i]);
      Vector normal = vertexNormals_[i] * 3;

      // Draw a line from (vertex - normal) to (vertex + normal)
      jdVertexv(vertex - normal);
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
   double xMin = 0, yMin = 0, zMin = 0;
   double xMax = 0, yMax = 0, zMax = 0;

   for (int i = 0; i < data_->num_xyz; i++)
   {
      Vector vertex = Vector(data_->m_vertices[i]);
      
      xMin = qMin(xMin, vertex.x);
      yMin = qMin(yMin, vertex.y);
      zMin = qMin(zMin, vertex.z);

      xMax = qMax(xMax, vertex.x);
      yMax = qMax(yMax, vertex.y);
      zMax = qMax(zMax, vertex.z);
   }

   Vector minimum = Vector(xMin, yMin, zMin);
   Vector maximum = Vector(xMax, yMax, zMax);

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
      Vector normal = line01.cross(line02).normalized(); 

      // Save the calculated normal
      faceNormals_[i] = normal;

      // While we're here, save the face center
      faceCenters_[i] = (vertex0 + vertex1 + vertex2) * (1.0/3.0);
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
         averageNormal += (faceNormals_[triangleId] / triangles.count());
      }

      // Save the resulting normal
      vertexNormals_[vertexId] = averageNormal;
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

