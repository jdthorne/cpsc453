
// 3rdparty
#include <md2.h>

// System
#include <OpenGl.h>

// Qt
#include <QList>

// Project
#include <ModelRenderer.h>
#include <RenderHelpers.h>
#include <Vector.h>

using namespace RenderHelpers;

ModelRenderer::ModelRenderer()
   : renderMode_(SmoothShading)
   , displayNormals_(false)
{
   models_.append(new Model("models/battroid/tris.md2"));
   models_.append(new Model("models/battroid/weapon.md2"));
}

ModelRenderer::~ModelRenderer()
{
}

/**
 ******************************************************************************
 *
 *                   Settings
 *
 ******************************************************************************
 */
void ModelRenderer::setRenderMode(RenderMode mode)
{
   renderMode_ = mode;
   emit optionsChanged();
}

void ModelRenderer::setTranslation(Vector translation)
{
   translation_ = translation;
   emit optionsChanged();
}

void ModelRenderer::setDisplayNormals(bool displayNormals)
{
   displayNormals_ = displayNormals;
   emit optionsChanged();
}

/**
 ******************************************************************************
 *
 *                   Rendering
 *
 ******************************************************************************
 */
void ModelRenderer::render()
{
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   setupRenderMode();
   setupEyePosition();
   setupTransformation();

   foreach(Model* model, models_)
   {
      renderModel(*model);
      renderNormalsIfNecessary(*model);
   }
}

void ModelRenderer::setupRenderMode()
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

void ModelRenderer::setupEyePosition()
{
   Vector center = models_[0]->center();
   Vector size = models_[0]->size();

   double maxSize = size.largestElement();
   double distanceRequiredToViewEntireModel = maxSize * 1.5;

   gluLookAt(distanceRequiredToViewEntireModel, 0, 0, 
             center.x, center.y, center.z,
             0, 0, 1);
}

void ModelRenderer::setupTransformation()
{
   glTranslatev(translation_);
}

void ModelRenderer::renderModel(Model& model)
{
   glEnable(GL_LIGHTING);

   glColor3f(1, 0, 0);
   glBegin(GL_TRIANGLES);
   for (int i = 0; i < model.data().num_tris; i++)
   {
      triangle_t triangle = model.data().tris[i];

      for (int v = 0; v < 3; v++)
      {
         int vertexId = triangle.index_xyz[v];

         Vector vertex = Vector(model.data().m_vertices[vertexId]);
         Vector normal = model.vertexNormals()[vertexId] * -1;

         glNormalv(normal);
         glVertexv(vertex);
      }
   }
   glEnd();

   glDisable(GL_LIGHTING);
}

void ModelRenderer::renderNormalsIfNecessary(Model& model)
{
   if (!displayNormals_)
   {
      return;
   }

   glBegin(GL_LINES);

   glColor3f(0, 1, 0);
   for (int i = 0; i < model.data().num_tris; i++)
   {
      Vector centerOfFace = model.faceCenters()[i];
      Vector normal = model.faceNormals()[i] * 3;

      glVertexv(centerOfFace - normal);
      glVertexv(centerOfFace + normal);
   }

   glColor3f(0, 0, 1);
   for (int i = 0; i < model.data().num_xyz; i++)
   {
      Vector vertex = Vector(model.data().m_vertices[i]);
      Vector normal = model.vertexNormals()[i] * 3;

      glVertexv(vertex - normal);
      glVertexv(vertex + normal);
   }

   glEnd();
}
