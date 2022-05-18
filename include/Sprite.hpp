// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Sprite class - Header file.

// Define guard.
#ifndef SPRITE_H_
#define SPRITE_H_

// Includes.
#include <string>

// User includes.
#include "GameObject.hpp"
#include "Texture.hpp"

// Declarations.
class Sprite;

// Class definition.
class Sprite : public Component {
  // Public components.
  public:

    // Class method prototypes.
    Sprite(GameObject& associated);
    Sprite(GameObject& associated, SDL_Renderer* renderer, std::string file);

    // Method prototypes.
    void open(SDL_Renderer* renderer, std::string file);
    void render(SDL_Renderer* renderer) const noexcept override;
    void update(double dt) noexcept override;

  // Private components.
  private:

    // Members.
    Texture texture;

    // Method prototypes.
    void setAssociatedGameObjectDimensions() noexcept;
};

#endif // SPRITE_H_
