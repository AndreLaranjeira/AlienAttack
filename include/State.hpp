// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - State class - Header file.

// Define guard.
#ifndef STATE_H_
#define STATE_H_

// Includes.
#include <cmath>
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
#include "Face.hpp"
#include "GameObject.hpp"
#include "Music.hpp"
#include "Sound.hpp"
#include "Sprite.hpp"
#include "VectorR2.hpp"

// Declarations.
struct BackgroundParams;
struct EnemyParams;
class State;

// Macros.
#define BACKGROUND_SPRITE_FILE "./assets/img/ocean.jpg"
#define ENEMY_SOUND_FILE "./assets/audio/boom.wav"
#define ENEMY_SPRITE_FILE "./assets/img/penguinface.png"
#define STATE_MUSIC_FILE "./assets/audio/stage_state.ogg"

// Type definitions.
struct BackgroundParams {
  std::string sprite_file;
};

struct EnemyParams {
  std::string sprite_file;
  std::string sound_file;
  VectorR2 coordinates;
};

// Class definition.
class State {
  // Public components.
  public:

    // Class method prototypes.
    State(SDL_Renderer* renderer);

    // Method prototypes.
    void loadAssets();
    void processInput();
    bool quitRequested() const noexcept;
    void renderAndPresent();
    void update(double dt);

  // Private components.
  private:

    // Members.
    Music music;
    std::vector<std::unique_ptr<GameObject>> objectArray;
    bool quit_requested = false;
    SDL_Renderer* renderer;

    // Method prototypes.
    void addBackgroundGameObject(const BackgroundParams& background_params);
    void addEnemyGameObject(const EnemyParams& enemy_params);
    void addGameObject(GameObject* new_game_object);
    int applyDamageToGameObject(
      std::unique_ptr<GameObject>& damage_target,
      unsigned int damage
    );
    game_object_iter convertReverseIterToIter(
      game_object_reverse_iter reverse_iterator
    ) const;
    bool gameObjectFinishedPlayingDeathSound(
      std::unique_ptr<GameObject>& game_object
    ) const noexcept;
    bool gameObjectIsAptForDeletion(
      std::unique_ptr<GameObject>& game_object
    ) const noexcept;
    void handleClickOnGameObject(game_object_iter target_iter);
    void handleEvent(
      const SDL_Event& event,
      const VectorR2& mouse_coordinates
    );
    void handleKeyDown(
      const SDL_Keysym& keysym,
      const VectorR2& mouse_coordinates
    );
    void handleMouseButtonDown(const VectorR2& mouse_coordinates);
    game_object_iter livingGameObjectWithLeastDepthLocatedAt(
      const VectorR2& search_coordinates
    );
    VectorR2 mouseCoordinates() const noexcept;
    void playMusic() noexcept;
    VectorR2 randomCoordinatesWithMagnitude(
      unsigned int coordinates_magnitude
    ) const noexcept;
    void removeGameObjectAt(size_t index);
    void removeGameObjectsWhoseDeletionWasRequested();
    void renderGameObjects();
    void requestDeletionOfGameObjectsAptForDeletion() noexcept;
    void stopMusic() noexcept;
    void updateGameObjects(double dt);
};

#endif // STATE_H_
