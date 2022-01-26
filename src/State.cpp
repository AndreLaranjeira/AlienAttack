// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - State class - Source code.

// Class header include.
#include "State.hpp"

// Class method implementations.
State::State(SDL_Renderer* renderer) try :
  bg(renderer, "./assets/img/ocean.jpg"),
  music("./assets/audio/stage_state.ogg")
{
  this->playMusic();
}
catch(exception& e) {
  throw;
};

// Public method implementations.
void State::loadAssets() {};

bool State::quitRequested() {
  return this->quit_requested;
};

void State::render(SDL_Renderer* renderer) {
  bg.render(renderer, 0, 0);
};

void State::update(double dt) {
  if(SDL_QuitRequested() == SDL_TRUE)
    this->quit_requested = true;
};

// Private method implementations.
void State::playMusic() {
  try {
    this->music.play();
  }
  catch(exception& e) {
    cerr << "[State] " << e.what();
    cerr << "[State] Ignoring previous exception and continuing execution!\n";
  }
};