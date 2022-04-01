// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Vector R2 class - Source code.

// Class header include.
#include "VectorR2.hpp"

// Class method implementations.
VectorR2::VectorR2(double x, double y) noexcept : x(x), y(y) {};

// Public method implementations.
double VectorR2::angleInRadiansFromSelfTo(
  const VectorR2& reference
) const noexcept {
  return acos(
    this->dotProductWith(reference)/(this->magnitude() * reference.magnitude())
  );
};

double VectorR2::angleInRadiansFromXAxisToSelf() const noexcept {
  return atan2(this->y, this->x);
};

double VectorR2::angleInRadiansFromXAxisToSlopeConnectingSelfTo(
  const VectorR2& reference
) const noexcept {
  return (reference - *this).angleInRadiansFromXAxisToSelf();
};

VectorR2 VectorR2::clockwiseRotatedVector(
  double rotation_angle_in_radians
) const noexcept {
  double rot_angle_sin = sin(rotation_angle_in_radians); 
  double rot_angle_cos = cos(rotation_angle_in_radians); 

  return VectorR2(
    this->x * rot_angle_cos - this->y * rot_angle_sin,
    this->y * rot_angle_cos + this->x * rot_angle_sin
  );
};

VectorR2 VectorR2::counterClockwiseRotatedVector(
  double rotation_angle_in_radians
) const noexcept {
  return this->clockwiseRotatedVector(-rotation_angle_in_radians);
};

double VectorR2::distanceTo(const VectorR2& reference) const noexcept {
  return (*this - reference).magnitude();
};

double VectorR2::dotProductWith(const VectorR2& vector) const noexcept {
  return (this->x * vector.x) + (this->y * vector.y);
};

double VectorR2::magnitude() const noexcept {
  return sqrt(pow(this->x, 2) + pow(this->y, 2));
};

VectorR2 VectorR2::normalizedVector() const noexcept {
  double vector_magnitude = this->magnitude();

  return VectorR2(
    this->x / vector_magnitude,
    this->y / vector_magnitude
  );
};

void VectorR2::normalizeSelf() noexcept {
  *this = this->normalizedVector();
};

void VectorR2::rotateSelfClockwise(double rotation_angle_in_radians) noexcept {
  *this = this->clockwiseRotatedVector(rotation_angle_in_radians);
};

void VectorR2::rotateSelfCounterClockwise(
  double rotation_angle_in_radians
) noexcept {
  *this = this->counterClockwiseRotatedVector(rotation_angle_in_radians);
};

// Class operator implementations.
VectorR2 operator + (const VectorR2& lhs, const VectorR2& rhs) noexcept {  
  return VectorR2(
    lhs.x + rhs.x,
    lhs.y + rhs.y
  );
};

void operator += (VectorR2& lhs, const VectorR2& rhs) noexcept {
  lhs = lhs + rhs;
};

VectorR2 operator - (const VectorR2& operand) noexcept {
  return VectorR2(
    -operand.x,
    -operand.y
  );
}

VectorR2 operator - (const VectorR2& lhs, const VectorR2& rhs) noexcept {  
  return lhs + (-rhs);
};

void operator -= (VectorR2& lhs, const VectorR2& rhs) noexcept {
  lhs = lhs - rhs;
};

VectorR2 operator * (const double scalar, const VectorR2& vector) noexcept {
  return VectorR2(
    scalar * vector.x,
    scalar * vector.y
  );
};

VectorR2 operator * (const VectorR2& vector, const double scalar) noexcept {
  return scalar * vector;
};
