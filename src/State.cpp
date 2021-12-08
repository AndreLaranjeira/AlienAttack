// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - State class - Source code.

// Includes.
#include "State.hpp"

// Class method implementations.
State::State() {};

State::~State() {};

// Public method implementations.
void State::LoadAssets() {};

bool State::QuitRequested() {
  return this->quitRequested;
};

void State::Render() {};

void State::Update() {
  if(SDL_QuitRequested() == SDL_TRUE)
    this->quitRequested = true;
};

// Private method implementations.
