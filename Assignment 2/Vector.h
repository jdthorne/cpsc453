
#ifndef VECTOR_H
#define VECTOR_H

#include <QString>

class Vector
{

public:
   Vector();
   Vector(double x, double y, double z);
   Vector(float coords[]);

public: // Operators
   Vector& operator += (const Vector& rhs);
   Vector operator + (const Vector& rhs) const;
   Vector operator - (const Vector& rhs) const;

   double largestElement() const;

   Vector cross(const Vector& rhs) const;
   double dot(const Vector& rhs) const;

   void normalize();

   Vector inverse() const;
   Vector normalized() const;

   Vector multiplyElementsBy(const Vector& rhs) const;

   QString toString() const;

   Vector boundedToMagnitude(double maxMagnitude) const;

   double magnitude() const;
   double distanceTo(const Vector rhs) const;

   static const Vector intersectionBetweenLineAndSphere(Vector lineStart, Vector direction,
                                                        Vector sphereCenter, double sphereRadius);

   static const Vector interpolate(Vector v1, Vector v2, double t);

public:
   double x;
   double y;
   double z;
};

#define printVec(vec) qPrintable(vec.toString())

Vector operator*(const Vector& vector, double scalar);
Vector operator/(const Vector& vector, double scalar);

#endif
