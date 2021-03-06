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
  return this->upper_left_corner + this->vectorFromUpperLeftCornerToCenter();
};

double Rectangle::distanceBetweenCenters(
  const Rectangle& reference
) const noexcept {
  return this->coordinatesOfCenter().distanceTo(
    reference.coordinatesOfCenter()
  );
};

bool Rectangle::isReferenceInsideOfSelf(
  const VectorR2& reference
) const noexcept {
  return (
    reference.x > this->upper_left_corner.x &&
    reference.x < this->upper_left_corner.x + width &&
    reference.y > this->upper_left_corner.y &&
    reference.y < this->upper_left_corner.y + height
  );
};

bool Rectangle::isReferenceOnTheBoundariesOfSelf(
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

bool Rectangle::isReferenceInsideOrOnTheBoundariesOfSelf(
  const VectorR2& reference
) const noexcept {
  return (
    reference.x >= this->upper_left_corner.x &&
    reference.x <= this->upper_left_corner.x + width &&
    reference.y >= this->upper_left_corner.y &&
    reference.y <= this->upper_left_corner.y + height
  );
};

VectorR2 Rectangle::vectorFromUpperLeftCornerToCenter() const noexcept {
  return VectorR2(
    this->width / 2,
    this-> height / 2
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
