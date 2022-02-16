// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Vector R2 class - Header file.

// Define guard.
#ifndef VECTOR_R2_H_
#define VECTOR_R2_H_

// Includes.
#include <cmath>

// Namespace.
using namespace std;

// Class definition.
class VectorR2 {
  // Public components.
  public:

    // Class method prototypes.
    VectorR2() = default;
    VectorR2(double x, double y);

    // Members.
    double x = 0;
    double y = 0;

    // Method prototypes.
    double angleInRadiansFromSelfTo(VectorR2& reference);
    double angleInRadiansFromXAxisToSelf();
    VectorR2 clockwiseRotatedVector(double rotation_angle_in_radians);
    VectorR2 counterClockwiseRotatedVector(double rotation_angle_in_radians);
    double distanceTo(VectorR2& reference);
    double magnitude();
    VectorR2 normalizedVector();
    void normalizeSelf();
    void rotateSelfClockwise(double rotation_angle_in_radians);
    void rotateSelfCounterClockwise(double rotation_angle_in_radians);
};

// Class operator prototypes.
VectorR2 operator + (VectorR2& lhs, VectorR2& rhs);
void operator += (VectorR2& lhs, VectorR2& rhs);
VectorR2 operator - (VectorR2& lhs, VectorR2& rhs);
void operator -= (VectorR2& lhs, VectorR2& rhs);
VectorR2 operator * (double scalar, VectorR2& vector);
VectorR2 operator * (VectorR2& vector, double scalar);

#endif // VECTOR_R2_H_
