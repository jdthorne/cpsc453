#include <QtGlobal>

#include <Vector.h>
#include <cmath>

Vector::Vector()
   : x(0.0)
   , y(0.0)
   , z(0.0)
{
}

Vector::Vector(double x, double y, double z)
   : x(x)
   , y(y)
   , z(z)
{
}

Vector::Vector(float coords[])
   : x(coords[0])
   , y(coords[1])
   , z(coords[2])
{
}

/**
 ******************************************************************************
 *
 *                   Add another vector to this one
 *
 ******************************************************************************
 */
Vector& Vector::operator += (const Vector& rhs)
{
   x += rhs.x;
   y += rhs.y;
   z += rhs.z;

   return *this;
}

/**
 ******************************************************************************
 *
 *                   Add two vectors
 *
 ******************************************************************************
 */
Vector Vector::operator + (const Vector& rhs) const
{
   Vector result = *this;
   result += rhs;

   return result;
}

/**
 ******************************************************************************
 *
 *                   Subtract two vectors
 *
 ******************************************************************************
 */
Vector Vector::operator - (const Vector& rhs) const
{
   return Vector(x - rhs.x, y - rhs.y, z - rhs.z);
}

/**
 ******************************************************************************
 *
 *                   Return the largest individual element
 *
 ******************************************************************************
 */
double Vector::largestElement() const
{
   return qMax(qMax(x, y), z);
}

/**
 ******************************************************************************
 *
 *                   Cross product
 *
 ******************************************************************************
 */
Vector Vector::cross(const Vector& rhs) const
{
   const Vector& one = *this;
   const Vector& two = rhs;

   return Vector( (one.y * two.z) - (two.y * one.z),
                  (one.z * two.x) - (two.z * one.x),
                  (one.x * two.y) - (two.x * one.y) );
}

/**
 ******************************************************************************
 *
 *                   Dot product
 *
 ******************************************************************************
 */
double Vector::dot(const Vector& rhs) const
{
   return (x*rhs.x) + (y*rhs.y) + (z*rhs.z);
}

/**
 ******************************************************************************
 *
 *                   Return vector magnitude
 *
 ******************************************************************************
 */
double Vector::magnitude() const
{
   return sqrt(x*x + y*y + z*z);
}

/**
 ******************************************************************************
 *
 *                   Return a normalized vector (i.e. magnitude = 1)
 *
 ******************************************************************************
 */
Vector Vector::normalized() const
{
   Vector result = *this;
   result.normalize();
   return result;
}

/**
 ******************************************************************************
 *
 *                   Normalize this vector in place
 *
 ******************************************************************************
 */
void Vector::normalize()
{
   double scale = magnitude();
   x /= scale;
   y /= scale;
   z /= scale;
}

/**
 ******************************************************************************
 *
 *                   Multiply by a scalar
 *
 ******************************************************************************
 */
Vector operator*(const Vector& vector, double scalar)
{
   return Vector(vector.x * scalar, vector.y * scalar, vector.z * scalar);
}

/**
 ******************************************************************************
 *
 *                   Divide by a scalar
 *
 ******************************************************************************
 */
Vector operator/(const Vector& vector, double scalar)
{
   return Vector(vector.x / scalar, vector.y / scalar, vector.z / scalar);
}

/**
 ******************************************************************************
 *
 *                   Return a string representation (for debugging)
 *
 ******************************************************************************
 */
QString Vector::toString() const
{
   return QString::number(x, 'f', 6) + " " + QString::number(y, 'f', 6) + " " + QString::number(z, 'f', 6);
}

/**
 ******************************************************************************
 *
 *                   Calculate the inverse of this vector
 *
 ******************************************************************************
 */
Vector Vector::inverse() const
{
   return Vector(1.0/x, 1.0/y, 1.0/z);
}

/**
 ******************************************************************************
 *
 *                   Multiply element-wise
 *
 ******************************************************************************
 */
Vector Vector::multiplyElementsBy(const Vector& rhs) const
{
   return Vector(x*rhs.x, y*rhs.y, z*rhs.z);
}

/**
 ******************************************************************************
 *
 *                   Bound to a maximum magnitude
 *
 ******************************************************************************
 */
Vector Vector::boundedToMagnitude(double maxMagnitude) const
{
   double currentMagnitude = this->magnitude();
   if (currentMagnitude < maxMagnitude)
   {
      return *this;
   }

   double scale = currentMagnitude / maxMagnitude;
   return (*this) * (1.0/scale);
}

/**
 ******************************************************************************
 *
 *                   Calculate the distance between vectors
 *
 ******************************************************************************
 */
double Vector::distanceTo(const Vector rhs) const
{
   return (*this - rhs).magnitude();
}

/**
 ******************************************************************************
 *
 *                   Interpolate two vectors by a scaling factor
 *
 ******************************************************************************
 */
const Vector Vector::interpolate(Vector v1, Vector v2, double t)
{
   return (v1 * t) + (v2 * (1.0 - t));
}

