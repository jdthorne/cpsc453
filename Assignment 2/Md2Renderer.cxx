
// 3rdparty
#include <md2.h>

// System
#include <OpenGl.h>

// Qt
#include <QList>

// Project
#include <Md2Renderer.h>
#include <RenderHelpers.h>
#include <Vector.h>

using namespace RenderHelpers;

Md2Renderer::Md2Renderer()
   : renderMode_(SmoothShading)
   , displayNormals_(false)
{
   model_ = new MD2();
   model_->LoadModel("models/cobra/tris.md2");

   calculateFaceNormals();
   calculateVertexNormals();
}

Md2Renderer::~Md2Renderer()
{
}

/**
 ******************************************************************************
 *
 *                   Settings
 *
 ******************************************************************************
 */
void Md2Renderer::setRenderMode(RenderMode mode)
{
   renderMode_ = mode;
   emit optionsChanged();
}

void Md2Renderer::setTranslation(Vector translation)
{
   translation_ = translation;
   emit optionsChanged();
}

void Md2Renderer::setDisplayNormals(bool displayNormals)
{
   displayNormals_ = displayNormals;
   emit optionsChanged();
}


/**
 ******************************************************************************
 *
 *                   Model Loading & Calculations
 *
 ******************************************************************************
 */
void Md2Renderer::calculateFaceNormals()
{
   for (int i = 0; i < model_->num_tris; i++)
   {
      const triangle_t& triangle = model_->tris[i];

      Vector vertex0 = Vector(model_->m_vertices[triangle.index_xyz[0]]);
      Vector vertex1 = Vector(model_->m_vertices[triangle.index_xyz[1]]);
      Vector vertex2 = Vector(model_->m_vertices[triangle.index_xyz[2]]);

      Vector line01 = vertex1 - vertex0;
      Vector line02 = vertex2 - vertex0;
      Vector normal = line01.cross(line02).normalized(); 

      faceNormals_[i] = normal;
      faceCenters_[i] = (vertex0 + vertex1 + vertex2) * (1.0/3.0);
   }   
}

void Md2Renderer::calculateVertexNormals()
{
   for (int vertexId = 0; vertexId < model_->num_xyz; vertexId++)
   {
      // Find the triangles that include this vertex
      QList<int> triangles;
      for (int triangleId = 0; triangleId < model_->num_tris; triangleId++)
      {
         const triangle_t& triangle = model_->tris[triangleId];
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
 *                   Rendering
 *
 ******************************************************************************
 */
void Md2Renderer::render()
{
   setupRenderMode();

   glPushMatrix();

   glTranslatev(translation_);
   glRotatef(-90, 1, 0, 0);

   glEnable(GL_LIGHTING);
   glColor3f(1, 0, 0);
   glBegin(GL_TRIANGLES);
   for (int i = 0; i < model_->num_tris; i++)
   {
      renderTriangle(model_->tris[i]);
   }
   glEnd();
   glDisable(GL_LIGHTING);

   if (displayNormals_)
   {
      glBegin(GL_LINES);
      glColor3f(0, 1, 0);
      for (int i = 0; i < model_->num_tris; i++)
      {
         Vector centerOfFace = faceCenters_[i];
         Vector normal = faceNormals_[i] * 3;

         glVertexv(centerOfFace - normal);
         glVertexv(centerOfFace + normal);
      }

      glColor3f(0, 0, 1);
      for (int i = 0; i < model_->num_xyz; i++)
      {
         Vector vertex = Vector(model_->m_vertices[i]);
         Vector normal = vertexNormals_[i] * 3;

         glVertexv(vertex - normal);
         glVertexv(vertex + normal);
      }
      glEnd();
   }

   glPopMatrix();
}

void Md2Renderer::setupRenderMode()
{
   switch (renderMode_)
   {
      case Wireframe:
      {
         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
         break;
      }
      case FlatShading:
      {
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
         glShadeModel(GL_FLAT);
         break;
      }
      case SmoothShading:
      {
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
         glShadeModel(GL_SMOOTH);
         break;
      }
   }
}

void Md2Renderer::renderTriangle(triangle_t& triangle)
{
   for (int i = 0; i < 3; i++)
   {
      int vertexId = triangle.index_xyz[i];

      Vector vertex = Vector(model_->m_vertices[vertexId]);
      Vector normal = vertexNormals_[vertexId] * -1;

      glNormalv(normal);
      glVertexv(vertex);
   }
}

