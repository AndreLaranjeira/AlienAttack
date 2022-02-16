// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Vector R2 class - Source code.

// Class header include.
#include "VectorR2.hpp"

// Class method implementations.
VectorR2::VectorR2(double x, double y) : x(x), y(y) {};

// Method implementations.
double VectorR2::angleInRadiansFromSelfTo(VectorR2& reference) {
  return (*this - reference).angleInRadiansFromXAxisToSelf();
};

double VectorR2::angleInRadiansFromXAxisToSelf() {
  return atan2(this->y, this->x);
};

VectorR2 VectorR2::clockwiseRotatedVector(
  double rotation_angle_in_radians
) {
  double rot_angle_sin = sin(rotation_angle_in_radians); 
  double rot_angle_cos = cos(rotation_angle_in_radians); 

  return VectorR2(
    this->x * rot_angle_cos - this->y * rot_angle_sin,
    this->y * rot_angle_cos + this->x * rot_angle_sin
  );
};

VectorR2 VectorR2::counterClockwiseRotatedVector(
  double rotation_angle_in_radians
) {
  return this->clockwiseRotatedVector(-rotation_angle_in_radians);
};

double VectorR2::distanceTo(VectorR2& reference) {
  return (*this - reference).magnitude();
};

double VectorR2::magnitude() {
  return sqrt(pow(this->x, 2) + pow(this->y, 2));
};

VectorR2 VectorR2::normalizedVector() {
  double vector_magnitude = this->magnitude();

  return VectorR2(
    this->x / vector_magnitude,
    this->y / vector_magnitude
  );
};

void VectorR2::normalizeSelf() {
  *this = this->normalizedVector();
};

void VectorR2::rotateSelfClockwise(double rotation_angle_in_radians) {
  *this = this->clockwiseRotatedVector(rotation_angle_in_radians);
};

void VectorR2::rotateSelfCounterClockwise(double rotation_angle_in_radians) {
  *this = this->counterClockwiseRotatedVector(rotation_angle_in_radians);
};

// Class operator implementations.
VectorR2 operator + (VectorR2& lhs, VectorR2& rhs) {  
  return VectorR2(
    lhs.x + rhs.x,
    lhs.y + rhs.y
  );
};

void operator += (VectorR2& lhs, VectorR2& rhs) {
  lhs = lhs + rhs;
};

VectorR2 operator - (VectorR2& lhs, VectorR2& rhs) {  
  return VectorR2(
    lhs.x - rhs.x,
    lhs.y - rhs.y
  );
};

void operator -= (VectorR2& lhs, VectorR2& rhs) {
  lhs = lhs - rhs;
};

VectorR2 operator * (double scalar, VectorR2& vector) {
  return VectorR2(
    scalar * vector.x,
    scalar * vector.y
  );
};

VectorR2 operator * (VectorR2& vector, double scalar) {
  return scalar * vector;
};