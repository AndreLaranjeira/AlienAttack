// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Game class - Source code.

// Class header include.
#include "Game.hpp"

// Static member initializations.
Game* Game::instance = nullptr; 

// Class method implementations.
Game::Game(GameParams game_params) {
  SDLConfig game_SDL_config = this->generateDefaultSDLConfig(game_params);

  try {
    this->initGame(game_SDL_config);
  }
  catch(GameInitException& game_init_exception) {
    this->cleanUpFailedGameInit(game_init_exception.getErrorCode());
    throw;
  }
};

Game::~Game() {
  this->cleanUpGameState();
  this->cleanUpGameRenderer();
  this->cleanUpGameWindow();
  this->cleanUpSDLModules();
};

// Public method implementations.
Game& Game::getInstance() {
  GameParams game_params = {
    .title = "AlienAttack",
    .width = 1024,
    .height = 600
  };

  if(Game::instance == nullptr) {
    try {
      Game::instance = new Game(game_params);
    }
    catch(std::exception& e) {
      throw;
    }
  }

  return *Game::instance;
};

SDL_Renderer* Game::getRenderer() const {
  return this->renderer;
};

State& Game::getState() const {
  return *(this->state);
};

void Game::run() {
  while (this->shouldKeepRunning()) {
    this->updateGameState();
    this->renderAndPresentGameState(this->renderer);
    this->waitTimeIntervalBetweenFrames();
  }
};

std::string GameInitErrorDescription::describeErrorCause(
  GameInitErrorCode error_code
) const {
  std::string error_cause = std::string("This error was caused by ");
  
  switch (error_code) {
    case GameInitErrorCode::DuplicateGameInstanceError:
      error_cause += "an attempt to create multiple game instances";
      break;
    case GameInitErrorCode::SDLError:
      error_cause += "the SDL module";
      break;
    case GameInitErrorCode::SDLImageError:
      error_cause += "the SDL Image module";
      break;
    case GameInitErrorCode::SDLMixError:
      error_cause += "the SDL Mixer module";
      break;
    case GameInitErrorCode::SDLAudioError:
      error_cause += "the SDL Audio functionality";
      break;
    case GameInitErrorCode::SDLWindowError:
      error_cause += "the SDL Window";
      break;
    case GameInitErrorCode::SDLRendererError:
      error_cause += "the SDL Renderer";
      break;
    case GameInitErrorCode::GameStateError:
      error_cause += "the internal Game State";
      break;
  }

  error_cause += ".";

  return error_cause;
};

std::string GameInitErrorDescription::describeErrorDetails(
  GameInitErrorCode error_code
) const {
  std::string error_details;

  switch (error_code) {
    case GameInitErrorCode::DuplicateGameInstanceError:
      error_details += "There can only be 1 instance of Game running";
      break;
    case GameInitErrorCode::SDLError:
    case GameInitErrorCode::SDLImageError:
    case GameInitErrorCode::SDLMixError:
    case GameInitErrorCode::SDLAudioError:
    case GameInitErrorCode::SDLWindowError:
    case GameInitErrorCode::SDLRendererError:
      error_details += SDL_GetError();
      break;
    case GameInitErrorCode::GameStateError:
      error_details += "The Game State constructor threw an exception";
      break;
  }

  error_details += ".";

  return error_details;
};

std::string GameInitErrorDescription::describeErrorSummary() const {
  std::string error_summary = std::string(
    "GameInitError: An error occurred when initializing the Game!"
  );

  return error_summary;
};

// Private method implementations.
void Game::cleanUpFailedGameInit(GameInitErrorCode error_code) {
  switch (error_code) {
    case GameInitErrorCode::GameStateError:
      this->cleanUpGameRenderer();

    case GameInitErrorCode::SDLRendererError:
      this->cleanUpGameWindow();
      
    case GameInitErrorCode::SDLWindowError:
      Mix_CloseAudio();

    case GameInitErrorCode::SDLAudioError:
      Mix_Quit();

    case GameInitErrorCode::SDLMixError:
      IMG_Quit();

    case GameInitErrorCode::SDLImageError:
      SDL_Quit();

    case GameInitErrorCode::SDLError:
    case GameInitErrorCode::DuplicateGameInstanceError:
      ;
  }
};

void Game::cleanUpGameRenderer() {
  if(this->renderer != nullptr) {
    SDL_DestroyRenderer(this->renderer);
    this->renderer = nullptr;
  }
};

void Game::cleanUpGameState() {
  if(this->state != nullptr) {
    delete this->state;
    this->state = nullptr;
  }
};

void Game::cleanUpGameWindow() {
  if(this->window != nullptr) {
    SDL_DestroyWindow(this->window);
    this->window = nullptr;
  }
};

void Game::cleanUpSDLModules() {
  Mix_CloseAudio();
  Mix_Quit();
  IMG_Quit();
  SDL_Quit();
};

SDLConfig Game::generateDefaultSDLConfig(GameParams game_params) const {
  return {
    .SDL_flags =  SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_VIDEO,
    .image_flags = IMG_INIT_JPG | IMG_INIT_PNG,
    .mixer_flags = MIX_INIT_OGG,
    .audio_params = {
      .frequency = MIX_DEFAULT_FREQUENCY,
      .format = MIX_DEFAULT_FORMAT,
      .output_channels = MIX_DEFAULT_CHANNELS,
      .chunksize = 1024
    },
    .mixer_channels = 32,
    .window_params = {
      .title = game_params.title.c_str(),
      .x_offset = SDL_WINDOWPOS_CENTERED,
      .y_offset = SDL_WINDOWPOS_CENTERED,
      .width = game_params.width,
      .height = game_params.height,
      .flags = 0
    },
    .renderer_params = {
      .index = -1,
      .flags = SDL_RENDERER_ACCELERATED
    },
  };
};

void Game::initGame(SDLConfig SDL_config) {
  if(this->verifySingletonProperty() != 0)
    throw GameInitException(GameInitErrorCode::DuplicateGameInstanceError);

  if(this->initSDL(SDL_config.SDL_flags) != 0)
    throw GameInitException(GameInitErrorCode::SDLError);

  if(this->initSDLImage(SDL_config.image_flags) != 0)
    throw GameInitException(GameInitErrorCode::SDLImageError); 

  if(this->initSDLMix(SDL_config.mixer_flags) != 0)
    throw GameInitException(GameInitErrorCode::SDLMixError);

  if(
    this->initSDLAudio(SDL_config.audio_params, SDL_config.mixer_channels) != 0
  )
    throw GameInitException(GameInitErrorCode::SDLAudioError);

  if(this->initSDLWindow(SDL_config.window_params) != 0)
    throw GameInitException(GameInitErrorCode::SDLWindowError);

  if(this->initSDLRenderer(SDL_config.renderer_params) != 0)
    throw GameInitException(GameInitErrorCode::SDLRendererError);

  if(this->initGameState() != 0)
    throw GameInitException(GameInitErrorCode::GameStateError);
};

int Game::initGameState() {
  try {
    this->state = new State(this->renderer);
  }
  catch(std::exception& e) {
    std::cerr << "[Game] " << e.what();
    return -1;
  }

  return 0;
};

int Game::initSDL(Uint32 SDL_flags) {
  if(SDL_Init(SDL_flags) == 0)
    return 0;
  else
    return -1;
};

int Game::initSDLAudio(SDLAudioParams audio_params, int mixer_channels) {
  if(
    Mix_OpenAudio(
      audio_params.frequency,
      audio_params.format,
      audio_params.output_channels,
      audio_params.chunksize
    ) == 0
  ) {
    Mix_AllocateChannels(mixer_channels);
    return 0;
  }
  else
    return -1;
};

int Game::initSDLImage(int image_flags) {
  if(IMG_Init(image_flags) == image_flags)
    return 0;
  else
    return -1;
};

int Game::initSDLMix(int mix_flags) {
  if(Mix_Init(mix_flags) == mix_flags)
    return 0;
  else
    return -1;  
};

int Game::initSDLRenderer(SDLRendererParams renderer_params) {
  this->renderer = SDL_CreateRenderer(
    this->window,
    renderer_params.index,
    renderer_params.flags
  );

  if(this->renderer != nullptr)
    return 0;
  else
    return -1;
};

int Game::initSDLWindow(SDLWindowParams window_params) {
  this->window = SDL_CreateWindow(
    window_params.title,
    window_params.x_offset,
    window_params.y_offset,
    window_params.width,
    window_params.height,
    window_params.flags
  );

  if(this->window != nullptr)
    return 0;
  else
    return -1;
};

void Game::renderAndPresentGameState(SDL_Renderer* state_renderer) {
  SDL_RenderClear(state_renderer);
  this->state->render(state_renderer);
  SDL_RenderPresent(state_renderer);
};

bool Game::shouldKeepRunning() const {
  return !(this->state->quitRequested());
};

void Game::updateGameState() {
  this->state->update(0);
};

int Game::verifySingletonProperty() const {
  if (Game::instance == nullptr)
    return 0;
  else
    return -1;
};

void Game::waitTimeIntervalBetweenFrames() const {
  SDL_Delay(33);
};
