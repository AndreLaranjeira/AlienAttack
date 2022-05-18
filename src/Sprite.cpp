// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Sprite class - Source code.

// Class header include.
#include "Sprite.hpp"

// Class method implementations.
Sprite::Sprite(
  GameObject& associated
) : Component(associated, ComponentType::SpriteComponent), texture() {
  this->attachToAssociatedGameObject();
};

Sprite::Sprite(
  GameObject& associated,
  SDL_Renderer* renderer,
  std::string file
) :
  Component(associated, ComponentType::SpriteComponent),
  texture(renderer, file)
{
  this->attachToAssociatedGameObject();
  this->setAssociatedGameObjectDimensions();
};

// Public method implementations.
void Sprite::open(SDL_Renderer* renderer, std::string file) {
  this->texture.open(renderer, file);
  this->setAssociatedGameObjectDimensions();
};

void Sprite::render(SDL_Renderer* renderer) const noexcept {
  this->texture.render(renderer, this->associated.box.upper_left_corner);
};

void Sprite::update(double dt) noexcept {};

// Private method implementations.
void Sprite::setAssociatedGameObjectDimensions() noexcept {
  this->associated.setDimensions(
    this->texture.getWidth(),
    this->texture.getHeight()
  );
};
