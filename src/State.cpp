// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - State class - Source code.

// Class header include.
#include "State.hpp"

// Class method implementations.
State::State() {};

State::~State() {};

// Public method implementations.
void State::loadAssets() {};

bool State::quitRequested() {
  return this->quit_requested;
};

void State::render() {};

void State::update() {
  if(SDL_QuitRequested() == SDL_TRUE)
    this->quit_requested = true;
};

// Private method implementations.
