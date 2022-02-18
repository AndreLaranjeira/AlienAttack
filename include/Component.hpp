// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Component class - Header file.

// Define guard.
#ifndef COMPONENT_H_
#define COMPONENT_H_

// Includes.
#include <string>

// User includes.
#include "GameObject.hpp"

// Namespace.
using namespace std;

// Class definition.
class Component {
  // Public components.
  public:

    // Class method prototypes.
    Component(GameObject& associated);
    virtual ~Component() = default;

    // Virtual method prototypes.
    virtual bool is(string type) const = 0;
    virtual void render() = 0;
    virtual void update(double dt) = 0;

  // Protected components.
  protected:

    // Members.
    GameObject& associated;
};

#endif // COMPONENT_H_
