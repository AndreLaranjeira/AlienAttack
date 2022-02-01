// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - State class - Header file.

// Define guard.
#ifndef STATE_H_
#define STATE_H_

// Includes.
#include <exception>
#include <iostream>
#include <string>

// SDL2 includes.
#include <SDL2/SDL.h>
#include <SDL2/SDL_quit.h>
#include <SDL2/SDL_stdinc.h>

// User includes.
#include "Music.hpp"
#include "Sprite.hpp"

// Namespace.
using namespace std;

// Class definition.
class State {
  // Public components.
  public:

    // Class method prototypes.
    State() = default;
    State(SDL_Renderer* renderer);

    // Method prototypes.
    void loadAssets();
    bool quitRequested();
    void render(SDL_Renderer* renderer);
    void update(double dt);

  // Private components.
  private:

    // Members.
    Sprite bg;
    Music music;
    bool quit_requested = false;

    // Method prototypes.
    bool musicIsUsingMixer();
    void playMusic();
    void stopMusic();
};

#endif // STATE_H_
