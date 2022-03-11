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

// Class definition.
class Face : public Component {
  // Public components.
  public:

    // Class method prototypes.
    Face(GameObject& associated);

    // Method prototypes.
    void registerDamage(unsigned int damage);
    void render(SDL_Renderer* renderer) override;
    void update(double dt) override;

  // Private components.
  private:

    // Members
    unsigned int hitpoints = 100;

    // Method prototypes.
    bool isDead() const;
    void handleDeath();
    void playDeathSound();
    void subtractDamageFromHitpoints(unsigned int damage);
};

#endif // FACE_H_
