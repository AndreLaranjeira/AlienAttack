// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Game class - Header file.

// Define guard.
#ifndef GAME_H_
#define GAME_H_

// Includes.
#include <cstddef>
#include <ctime>
#include <exception>
#include <iostream>
#include <string>

// SDL2 includes.
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

// User includes.
#include "State.hpp"

// Template includes.
#include "templates/ErrorDescription.hpp"
#include "templates/RuntimeException.hpp"

// Declarations.
class Game;
enum GameInitErrorCode : unsigned short;
class GameInitErrorDescription;
class GameInitException;
struct GameParams;
enum GameRunErrorCode : unsigned short;
class GameRunErrorDescription;
class GameRunException;
struct SDLConfig;

// Macros.
#define GAME_WINDOW_TITLE "AlienAttack"
#define GAME_WINDOW_HEIGHT 600
#define GAME_WINDOW_WIDTH 1024

// Enumeration definitions.
enum GameInitErrorCode : unsigned short {
  DuplicateGameInstanceError = 1,
  SDLError,
  SDLImageError,
  SDLMixError,
  SDLAudioError,
  SDLWindowError,
  SDLRendererError,
  GameStateError
};

enum GameRunErrorCode : unsigned short {
  StateUpdateError = 1,
  StateRenderAndPresentError
};

// Type definitions.
struct GameParams {
  std::string title;
  int width;
  int height;
};

struct SDLConfig {
  struct AudioParams {
    int frequency;
    Uint16 format;
    int output_channels;
    int chunksize;
  };

  struct RendererParams {
    int index;
    Uint32 flags;
  };

  struct WindowParams {
    const char* title;
    int x_offset;
    int y_offset;
    int width;
    int height;
    Uint32 flags;
  };

  Uint32 SDL_flags;
  int image_flags;
  int mixer_flags;
  AudioParams audio_params;
  int mixer_channels;
  WindowParams window_params;
  RendererParams renderer_params;
};

// Auxiliary class definitions.
class GameInitErrorDescription : public ErrorDescription<GameInitErrorCode> {
  // Public components.
  public:

    // Inherited methods.
    using ErrorDescription::ErrorDescription;

    // Method prototypes.
    std::string describeErrorCause(
      GameInitErrorCode error_code
    ) const noexcept override;
    std::string describeErrorDetails(
      GameInitErrorCode error_code
    ) const noexcept override;
    std::string describeErrorSummary() const noexcept override;
};

class GameRunErrorDescription : public ErrorDescription<GameRunErrorCode> {
  // Public components.
  public:

    // Inherited methods.
    using ErrorDescription::ErrorDescription;

    // Method prototypes.
    std::string describeErrorCause(
      GameRunErrorCode error_code
    ) const noexcept override;
    std::string describeErrorDetails(
      GameRunErrorCode error_code
    ) const noexcept override;
    std::string describeErrorSummary() const noexcept override;
};

// Exception definitions.
class GameInitException :
  public RuntimeException<GameInitErrorCode, GameInitErrorDescription>
{
  // Public components.
  public:

    // Inherited methods.
    using RuntimeException::RuntimeException;
};

class GameRunException :
  public RuntimeException<GameRunErrorCode, GameRunErrorDescription>
{
  // Public components.
  public:

    // Inherited methods.
    using RuntimeException::RuntimeException;
};

// Class definition.
class Game {
  // Public components.
  public:
  
    // Class method prototypes.
    ~Game() noexcept;

    // Method prototypes.
    SDL_Renderer* getRenderer() noexcept;
    State& getState() noexcept;
    void run();

    // Static method prototypes.
    static Game& getInstance();

  // Private components.
  private:

    // Class method prototypes.
    Game(GameParams game_params);
    Game(const Game&) = delete;

    // Members.
    SDL_Renderer* renderer = nullptr;
    State* state = nullptr;
    SDL_Window* window = nullptr;

    // Static members.
    static Game* instance;

    // Default operator overloadings.
    Game& operator = (const Game&) = delete;

    // Method prototypes.
    void cleanUpFailedGameInit(GameInitErrorCode error_code) noexcept;
    void cleanUpGameRenderer() noexcept;
    void cleanUpGameState() noexcept;
    void cleanUpGameWindow() noexcept;
    void cleanUpSDLModules() noexcept;
    SDLConfig defaultSDLConfig(GameParams game_params) const noexcept;
    void initGame(SDLConfig SDL_module_params);
    int initGameState() noexcept;
    void initRandomNumberGeneration() noexcept;
    int initSDL(Uint32 flags) noexcept;
    int initSDLAudio(
      SDLConfig::AudioParams audio_params,
      int audio_channels
    ) noexcept;
    int initSDLImage(int flags) noexcept;
    int initSDLMix(int flags) noexcept;
    int initSDLRenderer(SDLConfig::RendererParams renderer_params) noexcept;
    int initSDLWindow(SDLConfig::WindowParams window_params) noexcept;
    void renderAndPresentGameState();
    bool shouldKeepRunning() const noexcept;
    void updateGameState();
    int verifySingletonProperty() const noexcept;
    void waitTimeIntervalBetweenFrames() const noexcept;
};

#endif // GAME_H_
