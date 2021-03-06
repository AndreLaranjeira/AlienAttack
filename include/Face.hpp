// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Face class - Header file.

// Define guard.
#ifndef FACE_H_
#define FACE_H_

// Includes.
#include <iostream>

// SDL2 includes.
#include <SDL2/SDL_render.h>

// User includes.
#include "GameObject.hpp"
#include "Sound.hpp"

// Declarations.
class Face;

// Macros.
#define DEFAULT_HITPOINTS 100

// Class definition.
class Face : public Component {
  // Public components.
  public:

    // Class method prototypes.
    Face(GameObject& associated);

    // Method prototypes.
    void registerDamage(unsigned int damage);
    void render(SDL_Renderer* renderer) noexcept override;
    void update(double dt) noexcept override;

  // Private components.
  private:

    // Members
    unsigned int hitpoints = DEFAULT_HITPOINTS;

    // Method prototypes.
    void handleAssociatedGameObjectDeath();
    bool isDead() const noexcept;
    void playAssociatedGameObjectDeathSound() noexcept;
    void subtractDamageFromHitpoints(unsigned int damage) noexcept;
};

#endif // FACE_H_
