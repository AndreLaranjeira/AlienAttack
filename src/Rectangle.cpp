// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Rectangle class - Source code.

// Class header include.
#include "Rectangle.hpp"

// Class method implementations.
Rectangle::Rectangle(
  VectorR2 upper_left_corner,
  double width,
  double height
) noexcept :
  height(height),
  upper_left_corner(upper_left_corner),
  width(width) {};

// Public method implementations.
VectorR2 Rectangle::coordinatesOfCenter() const noexcept {
  return VectorR2(
    this->upper_left_corner.x + (this->width / 2),
    this->upper_left_corner.y + (this->height / 2)
  );
};

double Rectangle::distanceBetweenCenters(
  const Rectangle& reference
) const noexcept {
  return this->coordinatesOfCenter().distanceTo(
    reference.coordinatesOfCenter()
  );
};

bool Rectangle::isGivenReferenceInsideOfSelf(
  const VectorR2& reference
) const noexcept {
  return (
    reference.x > this->upper_left_corner.x &&
    reference.x < this->upper_left_corner.x + width &&
    reference.y > this->upper_left_corner.y &&
    reference.y < this->upper_left_corner.y + height
  );
};

bool Rectangle::isGivenReferenceOnTheBoundaryOfSelf(
  const VectorR2& reference
) const noexcept {
  return (
    (
      reference.x == this->upper_left_corner.x ||
      reference.x == this->upper_left_corner.x + width
    ) &&
    reference.y >= this->upper_left_corner.y &&
    reference.y <= this->upper_left_corner.y + height
  ) || (
    (
      reference.y == this->upper_left_corner.y ||
      reference.y == this->upper_left_corner.y + height
    ) &&
    reference.x > this->upper_left_corner.x &&
    reference.x < this->upper_left_corner.x + width
  );
};

bool Rectangle::isGivenReferenceInsideOrOnTheBoundaryOfSelf(
  const VectorR2& reference
) const noexcept {
  return (
    reference.x >= this->upper_left_corner.x &&
    reference.x <= this->upper_left_corner.x + width &&
    reference.y >= this->upper_left_corner.y &&
    reference.y <= this->upper_left_corner.y + height
  );
};

// Class operator implementations.
Rectangle operator + (
  const Rectangle& rectangle,
  const VectorR2& vectorR2
) noexcept {
  return Rectangle(
    rectangle.upper_left_corner + vectorR2,
    rectangle.width,
    rectangle.height
  );
};

Rectangle operator + (
  const VectorR2& vectorR2,
  const Rectangle& rectangle
) noexcept {
  return rectangle + vectorR2;
};

void operator += (Rectangle& rectangle, const VectorR2& vectorR2) noexcept {
  rectangle = rectangle + vectorR2;
};

Rectangle operator - (
  const Rectangle& rectangle,
  const VectorR2& vectorR2
) noexcept {
  return rectangle + (-vectorR2);
};

void operator -= (Rectangle& rectangle, const VectorR2& vectorR2) noexcept {
  rectangle = rectangle - vectorR2;
};
