// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Face class - Source code.

// Class header include.
#include "Face.hpp"

// Class method implementations.
Face::Face(
  GameObject& associated
) : Component(associated, ComponentType::FaceComponent) {
  this->attachToAssociatedGameObject();
};

// Public method implementations.
void Face::registerDamage(unsigned int damage) {
  this->subtractDamageFromHitpoints(damage);

  if(this->isDead())
    this->handleAssociatedGameObjectDeath();
};

void Face::render(SDL_Renderer* renderer) const noexcept {};

void Face::update(double dt) noexcept {};

// Private method implementations.
void Face::handleAssociatedGameObjectDeath() {
  this->playAssociatedGameObjectDeathSound();
  this->associated.resolveDeath();
};

bool Face::isDead() const noexcept {
  return this->hitpoints == 0;
};

void Face::playAssociatedGameObjectDeathSound() noexcept {
  Sound* associated_sound_component;

  associated_sound_component = static_cast<Sound*>(
    this->associated.getComponent(ComponentType::SoundComponent)
  );

  if(associated_sound_component != nullptr) {    
    try {
      associated_sound_component->play();
    }
    catch(PlaySoundException& play_sound_exception) {
      std::cerr << "[Face] " << play_sound_exception.what();
      std::cerr << "[Face] Ignoring last exception and resuming execution!\n";
    }
  }
};

void Face::subtractDamageFromHitpoints(unsigned int damage) noexcept {
  if(damage >= this->hitpoints)
    this->hitpoints = 0;

  else
    this->hitpoints -= damage;
};
