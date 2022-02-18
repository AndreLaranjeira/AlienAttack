// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Rectangle class - Header file.

// Define guard.
#ifndef RECTANGLE_H_
#define RECTANGLE_H_

// User includes.
#include "VectorR2.hpp"

// Namespace.
using namespace std;

// Class definition.
class Rectangle {
  // Public components.
  public:

    // Class method prototypes.
    Rectangle() = default;
    Rectangle(VectorR2 upper_left_corner, double width, double height);

    // Members.
    double height = 0;
    VectorR2 upper_left_corner;
    double width = 0;

    // Method prototypes.
    VectorR2 coordinatesOfCenter() const;
    double distanceBetweenCenters(const Rectangle& reference) const;
    bool isGivenReferenceInsideOfSelf(const VectorR2& reference) const;
    bool isGivenReferenceOnTheBoundaryOfSelf(const VectorR2& reference) const;
    bool isGivenReferenceInsideOrOnTheBoundaryOfSelf(
      const VectorR2& reference
    ) const;
};

// Class operator prototypes.
Rectangle operator + (const Rectangle& rectangle, const VectorR2& vectorR2);
Rectangle operator + (const VectorR2& vectorR2, const Rectangle& rectangle);
void operator += (Rectangle& rectangle, const VectorR2& vectorR2);
Rectangle operator - (const Rectangle& rectangle, const VectorR2& vectorR2);
void operator -= (Rectangle& rectangle, const VectorR2& vectorR2);

#endif // RECTANGLE_H_
