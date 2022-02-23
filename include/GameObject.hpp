// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Game Object class - Header file.

// Define guard.
#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

// Includes.
#include <algorithm>
#include <memory>
#include <string>
#include <vector>

// User includes.
#include "Rectangle.hpp"

// Declarations.
class Component;
class GameObject;

// Type definitions.
using component_const_iter = \
  std::vector<std::unique_ptr<Component>>::const_iterator;

// Auxiliary class definitions.
class Component {
  // Public components.
  public:

    // Class method prototypes.
    Component(GameObject& associated);
    virtual ~Component() = default;

    // Virtual method prototypes.
    virtual bool is(std::string type) const = 0;
    virtual void render() = 0;
    virtual void update(double dt) = 0;

  // Protected components.
  protected:

    // Members.
    GameObject& associated;
};

// Class definition.
class GameObject {
  // Public components.
  public:

    // Method prototypes.
    void addComponent(Component* new_component);
    Component* getComponent(std::string type);
    bool isDead() const;
    void removeComponent(Component* component_to_remove);
    void render();
    void requestDelete();
    void update(double dt);
    
    // Members.
    Rectangle box;

  // Private components.
  private:

    // Members.
    std::vector<std::unique_ptr<Component>> components;
    bool is_dead = false;

    // Method prototypes.
    component_const_iter searchComponentsByType(
      std::string search_parameter
    ) const;
    component_const_iter searchComponentsByValue(
      Component* search_parameter
    ) const;

};

#endif // GAME_OBJECT_H_
