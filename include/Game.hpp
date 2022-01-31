// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Game class - Header file.

// Define guard.
#ifndef GAME_H_
#define GAME_H_

// Includes.
#include <exception>
#include <iostream>
#include <stdexcept>
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

// Namespace.
using namespace std;

// Enumeration definitions.
enum GameInitErrorCode {
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
  string title;
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
class GameInitErrorDescription :
  public ErrorDescriptionTemplate<GameInitErrorCode>
{
  // Public components.
  public:

    // Inherited methods.
    using ErrorDescriptionTemplate::ErrorDescriptionTemplate;

    // Method prototypes.
    string describeErrorCause(GameInitErrorCode error_code) override;
    string describeErrorDetails(GameInitErrorCode error_code) override;
    string describeErrorSummary() override;
};

// Exception definitions.
class GameInitException :
  public RuntimeExceptionTemplate<
    GameInitErrorCode,
    GameInitErrorDescription
  > {
  // Public components.
  public:

    // Inherited methods.
    using RuntimeExceptionTemplate::RuntimeExceptionTemplate;
};

// Class definition.
class Game {
  // Public components.
  public:
  
    // Class method prototypes.
    ~Game();

    // Method prototypes.
    SDL_Renderer* getRenderer();
    State& getState();
    void run();

    // Static method prototypes.
    static Game& getInstance();

  // Private components.
  private:

    // Class method prototypes.
    Game(GameParams game_params);
    Game(const Game&) = delete;

    // Class operators.
    Game& operator=(const Game&) = delete;

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
    SDLConfig generateDefaultSDLConfig(GameParams game_params);
    void initGame(SDLConfig SDL_module_params);
    int initGameState();
    int initSDL(Uint32 flags);
    int initSDLAudio(SDLAudioParams audio_params, int audio_channels);
    int initSDLImage(int flags);
    int initSDLMix(int flags);
    int initSDLRenderer(SDLRendererParams renderer_params);
    int initSDLWindow(SDLWindowParams window_params);
    void renderAndPresentGameState(SDL_Renderer* renderer);
    bool shouldKeepRunning();
    void updateGameState();
    int verifySingletonProperty();
    void waitTimeIntervalBetweenFrames();
};

#endif // GAME_H_
