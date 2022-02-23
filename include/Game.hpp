// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Game class - Header file.

// Define guard.
#ifndef GAME_H_
#define GAME_H_

// Includes.
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
struct SDLAudioParams;
struct SDLConfig;
struct SDLRendererParams;
struct SDLWindowParams;

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

// Type definitions.
struct GameParams {
  std::string title;
  int width;
  int height;
};

struct SDLAudioParams {
  int frequency;
  Uint16 format;
  int output_channels;
  int chunksize;
};

struct SDLRendererParams {
  int index;
  Uint32 flags;
};

struct SDLWindowParams {
  const char* title;
  int x_offset;
  int y_offset;
  int width;
  int height;
  Uint32 flags;
};

struct SDLConfig {
  Uint32 SDL_flags;
  int image_flags;
  int mixer_flags;
  SDLAudioParams audio_params;
  int mixer_channels;
  SDLWindowParams window_params;
  SDLRendererParams renderer_params;
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
    ) const override;
    std::string describeErrorDetails(
      GameInitErrorCode error_code
    ) const override;
    std::string describeErrorSummary() const override;
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

// Class definition.
class Game {
  // Public components.
  public:
  
    // Class method prototypes.
    ~Game();

    // Method prototypes.
    SDL_Renderer* getRenderer() const;
    State& getState() const;
    void run();

    // Static method prototypes.
    static Game& getInstance();

  // Private components.
  private:

    // Class method prototypes.
    Game(GameParams game_params);
    Game(const Game&) = delete;

    // Default operator overloadings.
    Game& operator = (const Game&) = delete;

    // Members.
    SDL_Renderer* renderer = nullptr;
    State* state = nullptr;
    SDL_Window* window = nullptr;

    // Static members.
    static Game* instance;

    // Method prototypes.
    void cleanUpFailedGameInit(GameInitErrorCode error_code);
    void cleanUpGameRenderer();
    void cleanUpGameState();
    void cleanUpGameWindow();
    void cleanUpSDLModules();
    SDLConfig generateDefaultSDLConfig(GameParams game_params) const;
    void initGame(SDLConfig SDL_module_params);
    int initGameState();
    int initSDL(Uint32 flags);
    int initSDLAudio(SDLAudioParams audio_params, int audio_channels);
    int initSDLImage(int flags);
    int initSDLMix(int flags);
    int initSDLRenderer(SDLRendererParams renderer_params);
    int initSDLWindow(SDLWindowParams window_params);
    void renderAndPresentGameState(SDL_Renderer* renderer);
    bool shouldKeepRunning() const;
    void updateGameState();
    int verifySingletonProperty() const;
    void waitTimeIntervalBetweenFrames() const;
};

#endif // GAME_H_
