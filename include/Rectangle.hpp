// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Rectangle class - Header file.

// Define guard.
#ifndef RECTANGLE_H_
#define RECTANGLE_H_

// User includes.
#include "VectorR2.hpp"

// Declarations.
class Rectangle;

// Class definition.
class Rectangle {
  // Public components.
  public:

    // Class method prototypes.
    Rectangle() noexcept = default;
    Rectangle(
      VectorR2 upper_left_corner,
      double width,
      double height
    ) noexcept;

    // Members.
    double height = 0;
    VectorR2 upper_left_corner;
    double width = 0;

    // Method prototypes.
    VectorR2 coordinatesOfCenter() const noexcept;
    double distanceBetweenCenters(const Rectangle& reference) const noexcept;
    bool isReferenceInsideOfSelf(
      const VectorR2& reference
    ) const noexcept;
    bool isReferenceOnTheBoundariesOfSelf(
      const VectorR2& reference
    ) const noexcept;
    bool isReferenceInsideOrOnTheBoundariesOfSelf(
      const VectorR2& reference
    ) const noexcept;
    VectorR2 vectorFromUpperLeftCornerToCenter() const noexcept;
};

// Class operator prototypes.
Rectangle operator + (
  const Rectangle& rectangle,
  const VectorR2& vectorR2
) noexcept;
Rectangle operator + (
  const VectorR2& vectorR2,
  const Rectangle& rectangle
) noexcept;
void operator += (Rectangle& rectangle, const VectorR2& vectorR2) noexcept;
Rectangle operator - (
  const Rectangle& rectangle,
  const VectorR2& vectorR2
) noexcept;
void operator -= (Rectangle& rectangle, const VectorR2& vectorR2) noexcept;

#endif // RECTANGLE_H_
