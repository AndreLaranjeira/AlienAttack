// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - State class - Header file.

// Define guard.
#ifndef STATE_H_
#define STATE_H_

// Includes.
#include <cstddef>
#include <exception>
#include <iostream>
#include <memory>
#include <string>

// SDL2 includes.
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_quit.h>
#include <SDL2/SDL_stdinc.h>

// User includes.
#include "GameObject.hpp"
#include "Music.hpp"
#include "Sprite.hpp"
#include "VectorR2.hpp"

// Declarations.
class State;

// Class definition.
class State {
  // Public components.
  public:

    // Class method prototypes.
    State() = default;
    State(SDL_Renderer* renderer);

    // Method prototypes.
    void loadAssets();
    void processInput();
    bool quitRequested() const;
    void render(SDL_Renderer* renderer);
    void update(double dt);

  // Private components.
  private:

    // Members.
    Music music;
    std::vector<std::unique_ptr<GameObject>> objectArray;
    bool quit_requested = false;

    // Method prototypes.
    void addBackgroundGameObject(SDL_Renderer* renderer, std::string file);
    void addGameObject(GameObject* new_game_object);
    void handleEvent(SDL_Event& event);
    void handleKeyDown(SDL_Keysym& keysym);
    void handleMouseButtonDown(VectorR2& mouse_coordinates);
    VectorR2 mouseCoordinates() const;
    bool musicIsUsingMixer() const;
    void playMusic();
    void removeDeadGameObjects();
    void removeGameObjectAt(size_t index);
    void stopMusic();
    void updateGameObjects(double dt);
};

#endif // STATE_H_
