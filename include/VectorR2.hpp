// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Vector R2 class - Header file.

// Define guard.
#ifndef VECTOR_R2_H_
#define VECTOR_R2_H_

// Includes.
#include <cmath>

// Declarations.
class VectorR2;

// Class definition.
class VectorR2 {
  // Public components.
  public:

    // Class method prototypes.
    VectorR2() noexcept = default;
    VectorR2(double x, double y) noexcept;

    // Members.
    double x = 0;
    double y = 0;

    // Method prototypes.
    double angleInRadiansFromSelfTo(const VectorR2& reference) const noexcept;
    double angleInRadiansFromXAxisToSelf() const noexcept;
    VectorR2 clockwiseRotatedVector(
      double rotation_angle_in_radians
    ) const noexcept;
    VectorR2 counterClockwiseRotatedVector(
      double rotation_angle_in_radians
    ) const noexcept;
    double distanceTo(const VectorR2& reference) const noexcept;
    double dotProductWith(const VectorR2& vector) const noexcept;
    double magnitude() const noexcept;
    VectorR2 normalizedVector() const noexcept;
    void normalizeSelf() noexcept;
    void rotateSelfClockwise(double rotation_angle_in_radians) noexcept;
    void rotateSelfCounterClockwise(double rotation_angle_in_radians) noexcept;
};

// Class operator prototypes.
VectorR2 operator + (const VectorR2& lhs, const VectorR2& rhs) noexcept;
void operator += (VectorR2& lhs, const VectorR2& rhs) noexcept;
VectorR2 operator - (const VectorR2& operand) noexcept;
VectorR2 operator - (const VectorR2& lhs, const VectorR2& rhs) noexcept;
void operator -= (VectorR2& lhs, const VectorR2& rhs) noexcept;
VectorR2 operator * (double scalar, const VectorR2& vector) noexcept;
VectorR2 operator * (const VectorR2& vector, double scalar) noexcept;

#endif // VECTOR_R2_H_
