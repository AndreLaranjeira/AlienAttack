// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Game Object class - Header file.

// Define guard.
#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

// Includes.
#include <algorithm>
#include <memory>
#include <vector>

// SDL2 includes.
#include <SDL2/SDL_render.h>

// User includes.
#include "Rectangle.hpp"
#include "VectorR2.hpp"

// Declarations.
class Component;
enum ComponentType : unsigned short;
class GameObject;
enum GameObjectState : unsigned short;

// Enumeration definitions.
enum ComponentType : unsigned short {
  FaceComponent,
  SoundComponent,
  SpriteComponent
};

enum GameObjectState : unsigned short {
  AliveState,
  DeadState,
  DeletionState
};

// Type definitions.
using component_const_iter = \
  std::vector<std::unique_ptr<Component>>::const_iterator;
using game_object_const_iter = \
  std::vector<std::unique_ptr<GameObject>>::const_iterator;
using game_object_iter = \
  std::vector<std::unique_ptr<GameObject>>::iterator;  
using game_object_reverse_iter = \
  std::vector<std::unique_ptr<GameObject>>::reverse_iterator;

// Auxiliary class definitions.
class Component {
  // Public components.
  public:

    // Class method prototypes.
    Component(GameObject& associated, ComponentType type) noexcept;
    virtual ~Component() noexcept = default;

    // Method prototypes.
    void attachToAssociatedGameObject();
    bool is(ComponentType type) const noexcept;
    
    // Virtual method prototypes.
    virtual void render(SDL_Renderer* renderer) = 0;
    virtual void update(double dt) = 0;

  // Protected components.
  protected:

    // Members.
    GameObject& associated;

  // Private components.
  private:

    // Members.
    ComponentType type;
};

// Class definition.
class GameObject {
  // Public components.
  public:
    
    // Members.
    Rectangle box;

    // Method prototypes.
    void addComponent(Component* new_component);
    bool deletionWasRequested() const noexcept;
    Component* getComponent(ComponentType type) noexcept;
    GameObjectState getState() const noexcept;
    bool hasComponentType(ComponentType type) const noexcept;
    bool isAlive() const noexcept;
    void removeComponent(Component* component_to_remove);
    void removeComponent(ComponentType removal_target_type);
    void render(SDL_Renderer* renderer);
    void requestDeletion() noexcept;
    void resolveDeath();
    void setCenterCoordinates(const VectorR2& center_coordinates) noexcept;
    void setDimensions(double width, double height) noexcept;
    void update(double dt);

  // Private components.
  private:

    // Members.
    std::vector<std::unique_ptr<Component>> components;
    GameObjectState state = AliveState;

    // Method prototypes.
    component_const_iter searchComponentsByType(
      ComponentType search_parameter
    ) const noexcept;
    component_const_iter searchComponentsByValue(
      Component* search_parameter
    ) const noexcept;
};

#endif // GAME_OBJECT_H_
