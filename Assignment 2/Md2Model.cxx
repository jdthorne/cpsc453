
// System

// Qt
#include <QImage>

// Project
#include <Md2Model.h>
#include <RenderHelpers.h>
#include <TextureHelpers.h>

using namespace RenderHelpers;
using namespace TextureHelpers;

Md2Model::Md2Model(QString modelDataFilename, QString skinTextureFilename)
{
   data_ = new MD2();
   data_->LoadModel(qPrintable(modelDataFilename));

   QImage textureImage = loadImageFromFile(skinTextureFilename);

   texture_ = loadTexture(textureImage);
   textureWidth_ = textureImage.width();
   textureHeight_ = textureImage.height();

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
 *                   Rendering
 *
 ******************************************************************************
 */
void Md2Model::renderMesh()
{
   glEnable(GL_LIGHTING);
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texture_);

   glColor3f(1, 1, 1);
   glBegin(GL_TRIANGLES);
   for (int i = 0; i < data_->num_tris; i++)
   {
      triangle_t triangle = data_->tris[i];

      for (int v = 0; v < 3; v++)
      {
         int vertexId = triangle.index_xyz[v];
         int texId = triangle.index_st[v];

         Vector vertex = Vector(data_->m_vertices[vertexId]);
         Vector normal = vertexNormals_[vertexId] * -1;

         tex_coord& tex = data_->texs[texId];

         glNormalv(normal);
         glTexCoord2f((float)tex.u / textureWidth_, (float)tex.v / textureHeight_);
         glVertexv(vertex);
      }
   }
   glEnd();

   glDisable(GL_TEXTURE_2D);
   glDisable(GL_LIGHTING);
}

void Md2Model::renderNormals()
{
   glBegin(GL_LINES);

   glColor3f(0, 1, 0);
   for (int i = 0; i < data_->num_tris; i++)
   {
      Vector centerOfFace = faceCenters_[i];
      Vector normal = faceNormals_[i] * 3;

      glVertexv(centerOfFace - normal);
      glVertexv(centerOfFace + normal);
   }

   glColor3f(0, 0, 1);
   for (int i = 0; i < data_->num_xyz; i++)
   {
      Vector vertex = Vector(data_->m_vertices[i]);
      Vector normal = vertexNormals_[i] * 3;

      glVertexv(vertex - normal);
      glVertexv(vertex + normal);
   }

   glEnd();
}

/**
 ******************************************************************************
 *
 *                   Calculation & Setup
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

void Md2Model::calculateFaceNormals()
{
   for (int i = 0; i < data_->num_tris; i++)
   {
      const triangle_t& triangle = data_->tris[i];

      Vector vertex0 = Vector(data_->m_vertices[triangle.index_xyz[0]]);
      Vector vertex1 = Vector(data_->m_vertices[triangle.index_xyz[1]]);
      Vector vertex2 = Vector(data_->m_vertices[triangle.index_xyz[2]]);

      Vector line01 = vertex1 - vertex0;
      Vector line02 = vertex2 - vertex0;
      Vector normal = line01.cross(line02).normalized(); 

      faceNormals_[i] = normal;
      faceCenters_[i] = (vertex0 + vertex1 + vertex2) * (1.0/3.0);
   }   
}

void Md2Model::calculateVertexNormals()
{
   for (int vertexId = 0; vertexId < data_->num_xyz; vertexId++)
   {
      // Find the triangles that include this vertex
      QList<int> triangles;
      for (int triangleId = 0; triangleId < data_->num_tris; triangleId++)
      {
         const triangle_t& triangle = data_->tris[triangleId];
         if (   triangle.index_xyz[0] == vertexId
             || triangle.index_xyz[1] == vertexId
             || triangle.index_xyz[2] == vertexId)
         {
            triangles.append(triangleId);
         }
      }

      // Average their normals
      Vector averageNormal = Vector(0, 0, 0);
      foreach (int triangleId, triangles)
      {
         averageNormal += (faceNormals_[triangleId] / triangles.count());
      }

      // Save the normal
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

