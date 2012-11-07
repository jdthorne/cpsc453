
// System
#include <cmath>

// Project
#include <AffineMatrix.h>

AffineMatrix::AffineMatrix()
{
   // Initialize all the elements to zero
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

/**
 ******************************************************************************
 *
 *                   Assignment operator - just copies the elements
 *
 ******************************************************************************
 */
AffineMatrix AffineMatrix::operator=(const AffineMatrix& rhs)
{
   // Copy the elements
   for (int i = 0; i < 4; i++)
   {
      for (int j = 0; j < 4; j++)
      {
         element[i][j] = rhs.element[i][j];
      }
   }

   return *this;
}


/**
 ******************************************************************************
 *
 *                   Returns the identity matrix
 *
 ******************************************************************************
 */
AffineMatrix AffineMatrix::identity()
{
   AffineMatrix result;

   // Set each main diagonal element to 1.0
   for (int i = 0; i < 4; i++)
   {
      result.element[i][i] = 1.0;
   }

   return result;
}

/**
 ******************************************************************************
 *
 *                   Create an Affine transformation matrix from axis/angle
 *
 ******************************************************************************
 */
AffineMatrix AffineMatrix::fromAxisAngle(Vector axis, double angle)
{
   AffineMatrix result;

   // Adapted from the mathematical derivation on Wikipedia 
   // (http://en.wikipedia.org/wiki/Rotation_matrix#Rotation_matrix_from_axis_and_angle)
   result.element[0][0] = cos(angle) + (axis.x() * axis.x() * (1 - cos(angle)));
   result.element[1][0] = (axis.x() * axis.y() * (1 - cos(angle))) - (axis.z() * sin(angle));
   result.element[2][0] = (axis.x() * axis.z() * (1 - cos(angle))) + (axis.y() * sin(angle));

   result.element[0][1] = (axis.y() * axis.x() * (1 - cos(angle))) + (axis.z() * sin(angle));
   result.element[1][1] = cos(angle) + (axis.y() * axis.y() * (1 - cos(angle)));
   result.element[2][1] = (axis.y() * axis.z() * (1 - cos(angle))) - (axis.x() * sin(angle));

   result.element[0][2] = (axis.z() * axis.x() * (1 - cos(angle))) - (axis.y() * sin(angle));
   result.element[1][2] = (axis.z() * axis.y() * (1 - cos(angle))) + (axis.x() * sin(angle));
   result.element[2][2] = cos(angle) + (axis.z() * axis.z() * (1 - cos(angle)));

   result.element[3][3] = 1.0;

   return result;
}

/**
 ******************************************************************************
 *
 *                   Create an Affine translation matrix
 *
 ******************************************************************************
 */
AffineMatrix AffineMatrix::fromTranslationVector(Vector translation)
{
   // Start with the identity matrix
   AffineMatrix result = AffineMatrix::identity();

   // Set the right-hand column to (x, y, z)
   result.element[3][0] = translation.x();
   result.element[3][1] = translation.y();
   result.element[3][2] = translation.z();

   return result;
}

/**
 ******************************************************************************
 *
 *                   Create an Affine scale matrix
 *
 ******************************************************************************
 */
AffineMatrix AffineMatrix::fromScaleVector(Vector scale)
{
   // Start with the identity matrix
   AffineMatrix result = AffineMatrix::identity();

   // Set the main diagonal to (xScale, yScale, zScale)
   result.element[0][0] = scale.x();
   result.element[1][1] = scale.y();
   result.element[2][2] = scale.z();

   return result;
}

/**
 ******************************************************************************
 *
 *                   Multiply by a scalar
 *
 ******************************************************************************
 */
AffineMatrix operator*(const AffineMatrix& matrix, double scalar)
{
   AffineMatrix result;

   // Multiply each element by a scalar
   for (int i = 0; i < 4; i++)
   {
      for (int j = 0; j < 4; j++)
      {
         result.element[i][j] = matrix.element[i][j] * scalar;
      }
   }

   return result;
}

/**
 ******************************************************************************
 *
 *                   Multiply two matricies
 *
 ******************************************************************************
 */
AffineMatrix operator*(const AffineMatrix& lhs, const AffineMatrix& rhs)
{
   AffineMatrix result;

   // Walk through the elements...
   for (int i = 0; i < 4; i++)
   {
      for (int j = 0; j < 4; j++)
      {

         double newValue = 0;

         // Walk through the row/column
         for (int offset = 0; offset < 4; offset++)
         {
            // Multiply row by column
            newValue += (lhs.element[offset][j] * rhs.element[i][offset]);
         }

         // Save the value
         result.element[i][j] = newValue;
      }
   }

   return result;
}
