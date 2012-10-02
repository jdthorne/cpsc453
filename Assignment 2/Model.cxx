
// System

// Project
#include <Model.h>

Model::Model(QString filename)
{
   md2Data_ = new MD2();
   md2Data_->LoadModel(qPrintable(filename));

   calculateBounds();
   calculateFaceNormals();
   calculateVertexNormals();
}

Model::~Model()
{
   delete md2Data_;
}

void Model::calculateBounds()
{
   double xMin = 0, yMin = 0, zMin = 0;
   double xMax = 0, yMax = 0, zMax = 0;

   for (int i = 0; i < md2Data_->num_xyz; i++)
   {
      Vector vertex = Vector(md2Data_->m_vertices[i]);
      
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

void Model::calculateFaceNormals()
{
   for (int i = 0; i < md2Data_->num_tris; i++)
   {
      const triangle_t& triangle = md2Data_->tris[i];

      Vector vertex0 = Vector(md2Data_->m_vertices[triangle.index_xyz[0]]);
      Vector vertex1 = Vector(md2Data_->m_vertices[triangle.index_xyz[1]]);
      Vector vertex2 = Vector(md2Data_->m_vertices[triangle.index_xyz[2]]);

      Vector line01 = vertex1 - vertex0;
      Vector line02 = vertex2 - vertex0;
      Vector normal = line01.cross(line02).normalized(); 

      faceNormals_[i] = normal;
      faceCenters_[i] = (vertex0 + vertex1 + vertex2) * (1.0/3.0);
   }   
}

void Model::calculateVertexNormals()
{
   for (int vertexId = 0; vertexId < md2Data_->num_xyz; vertexId++)
   {
      // Find the triangles that include this vertex
      QList<int> triangles;
      for (int triangleId = 0; triangleId < md2Data_->num_tris; triangleId++)
      {
         const triangle_t& triangle = md2Data_->tris[triangleId];
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
MD2& Model::data()
{
   return *md2Data_;
}

QMap<int,Vector>& Model::faceCenters()
{
   return faceCenters_;   
}

QMap<int,Vector>& Model::faceNormals()
{
   return faceNormals_;
}

QMap<int,Vector>& Model::vertexNormals()
{
   return vertexNormals_;
}

Vector& Model::center()
{
   return center_;
}

Vector& Model::size()
{
   return size_;
}

