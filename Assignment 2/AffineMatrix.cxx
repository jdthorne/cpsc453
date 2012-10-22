
// System
#include <cmath>

// Project
#include <Euler.h>
#include <AffineMatrix.h>

AffineMatrix::AffineMatrix()
{
   for (int i = 0; i < 4; i++)
   {
      for (int j = 0; j < 4; j++)
      {
         element[i][j] = 0;
      }
   }
}

AffineMatrix::~AffineMatrix()
{
}

AffineMatrix AffineMatrix::operator=(const AffineMatrix& rhs)
{
   for (int i = 0; i < 4; i++)
   {
      for (int j = 0; j < 4; j++)
      {
         element[i][j] = rhs.element[i][j];
      }
   }

   return *this;
}


AffineMatrix AffineMatrix::identity()
{
   AffineMatrix result;
   for (int i = 0; i < 4; i++)
   {
      result.element[i][i] = 1.0;
   }

   return result;
}

// Adapted from Wikipedia 
// (http://en.wikipedia.org/wiki/Rotation_matrix#Rotation_matrix_from_axis_and_angle)
AffineMatrix AffineMatrix::fromAxisAngle(Vector axis, double angle)
{
   AffineMatrix result;

   result.element[0][0] = cos(angle) + (axis.x * axis.x * (1 - cos(angle)));
   result.element[1][0] = (axis.x * axis.y * (1 - cos(angle))) - (axis.z * sin(angle));
   result.element[2][0] = (axis.x * axis.z * (1 - cos(angle))) + (axis.y * sin(angle));

   result.element[0][1] = (axis.y * axis.x * (1 - cos(angle))) + (axis.z * sin(angle));
   result.element[1][1] = cos(angle) + (axis.y * axis.y * (1 - cos(angle)));
   result.element[2][1] = (axis.y * axis.z * (1 - cos(angle))) - (axis.x * sin(angle));

   result.element[0][2] = (axis.z * axis.x * (1 - cos(angle))) - (axis.y * sin(angle));
   result.element[1][2] = (axis.z * axis.y * (1 - cos(angle))) + (axis.x * sin(angle));
   result.element[2][2] = cos(angle) + (axis.z * axis.z * (1 - cos(angle)));

   result.element[3][3] = 1.0;

   return result;
}

AffineMatrix AffineMatrix::fromEuler(Euler euler)
{
   AffineMatrix yaw = AffineMatrix::fromAxisAngle(Vector(0, 0, 1), euler.yaw);
   AffineMatrix pitch = AffineMatrix::fromAxisAngle(Vector(1, 0, 0), euler.pitch);
   AffineMatrix roll = AffineMatrix::fromAxisAngle(Vector(0, 1, 0), euler.roll);

   return yaw * pitch * roll;
}

AffineMatrix operator*(const AffineMatrix& matrix, double scalar)
{
   AffineMatrix result;

   for (int i = 0; i < 4; i++)
   {
      for (int j = 0; j < 4; j++)
      {
         result.element[i][j] = matrix.element[i][j] * scalar;
      }
   }

   return result;
}

AffineMatrix operator*(const AffineMatrix& lhs, const AffineMatrix& rhs)
{
   AffineMatrix result;
   for (int i = 0; i < 4; i++)
   {
      for (int j = 0; j < 4; j++)
      {
         double newValue = 0;
         for (int offset = 0; offset < 4; offset++)
         {
            newValue += (lhs.element[offset][j] * rhs.element[i][offset]);
         }
         result.element[i][j] = newValue;
      }
   }

   return result;
}
