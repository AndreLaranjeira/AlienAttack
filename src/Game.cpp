// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Game class - Source code.

// Includes.
#include "Game.hpp"

// Static member initializations.
Game* Game::instance = nullptr; 

// Class method implementations.
Game::Game(GameParams game_params) {
  GameInitErrorCode game_init_error_code;
  GameInitStatusCode game_init_status_code;
  SDLConfig game_SDL_config;

  game_SDL_config = this->generateDefaultSDLConfig(game_params);
  game_init_status_code = this->initGame(game_SDL_config);

  if(holds_alternative<GameInitErrorCode>(game_init_status_code)) {
    game_init_error_code = get<GameInitErrorCode>(game_init_status_code);
    this->handleGameInitError(game_init_error_code);
  }

};

Game::~Game() {
  this->cleanUpGameState();
  this->cleanUpGameRenderer();
  this->cleanUpGameWindow();
  this->cleanUpSDLModules();
};

// Public method implementations.
Game& Game::GetInstance() {
  GameParams game_params = {
    .title = "AlienAttack",
    .width = 1024,
    .height = 600
  };

  if(Game::instance == nullptr) {
    try {
      Game::instance = new Game(game_params);
    }
    catch(exception &e) {
      throw;
    }
  }

  return *Game::instance;
};

SDL_Renderer* Game::GetRenderer(){
  return this->renderer;
};

State& Game::GetState(){
  return *(this->state);
};

void Game::Run(){
  while (this->state->QuitRequested() != true) {
    this->state->Update();

    this->state->Render();
    SDL_RenderPresent(this->renderer);
    
    SDL_Delay(33);
  }
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
  delete this->state;
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

string Game::describeGameInitErrorCode(GameInitErrorCode error_code) {
  string description = string("This error was caused by ");
  
  switch (error_code) {
    case GameInitErrorCode::DuplicateGameInstanceError:
      description += "an attempt to create multiple game instances";
      break;
    case GameInitErrorCode::SDLError:
      description += "the SDL module";
      break;
    case GameInitErrorCode::SDLImageError:
      description += "the SDL Image module";
      break;
    case GameInitErrorCode::SDLMixError:
      description += "the SDL Mixer module";
      break;
    case GameInitErrorCode::SDLAudioError:
      description += "the SDL Audio";
      break;
    case GameInitErrorCode::SDLWindowError:
      description += "the SDL Window";
      break;
    case GameInitErrorCode::SDLRendererError:
      description += "the SDL Renderer";
      break;
    case GameInitErrorCode::GameStateError:
      description += "the internal Game State";
      break;
  }

  description += ".";

  return description;
}

string Game::describeGameInitErrorDetails(GameInitErrorCode error_code) {
  string description = string("More details: ");

  switch (error_code) {
    case GameInitErrorCode::DuplicateGameInstanceError:
      description += "There can only be 1 instance of Game running";
      break;
    case GameInitErrorCode::SDLError:
    case GameInitErrorCode::SDLImageError:
    case GameInitErrorCode::SDLMixError:
    case GameInitErrorCode::SDLAudioError:
    case GameInitErrorCode::SDLWindowError:
    case GameInitErrorCode::SDLRendererError:
      description += SDL_GetError();
      break;
    case GameInitErrorCode::GameStateError:
      description += "The Game State constructor threw an exception";
  }

  description += ".";

  return description;
}

SDLConfig Game::generateDefaultSDLConfig(GameParams game_params) {
  return {
    .SDL_flags =  SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_VIDEO,
    .image_flags = IMG_INIT_JPG | IMG_INIT_PNG,
    .mixer_flags = MIX_INIT_OGG,
    .audio_params = {
      .frequency = MIX_DEFAULT_FREQUENCY,
      .format = MIX_DEFAULT_FORMAT,
      .output_channels = MIX_DEFAULT_CHANNELS,
      .chunksize = 1024,
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

void Game::handleGameInitError(GameInitErrorCode error_code) {
  this->cleanUpFailedGameInit(error_code);
  this->throwGameInitException(error_code);
};

GameInitStatusCode Game::initGame(SDLConfig SDL_config) {
  if(this->verifySingletonProperty() != 0)
    return GameInitErrorCode::DuplicateGameInstanceError;

  if(this->initSDL(SDL_config.SDL_flags) != 0)
    return GameInitErrorCode::SDLError;

  if(this->initSDLImage(SDL_config.image_flags) != 0)
    return GameInitErrorCode::SDLImageError; 

  if(this->initSDLMix(SDL_config.mixer_flags) != 0)
    return GameInitErrorCode::SDLMixError;

  if(
    this->initSDLAudio(SDL_config.audio_params, SDL_config.mixer_channels) != 0
  )
    return GameInitErrorCode::SDLAudioError;

  if(this->initSDLWindow(SDL_config.window_params) != 0)
    return GameInitErrorCode::SDLWindowError;

  if(this->initSDLRenderer(SDL_config.renderer_params) != 0)
    return GameInitErrorCode::SDLRendererError;

  if(this->initGameState() != 0)
    return GameInitErrorCode::GameStateError;

  return GameInitSuccessCode::GameInitSuccess;
};

int Game::initGameState() {
  try {
    this->state = new State();
  }
  catch(exception &e) {
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
}

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

void Game::throwGameInitException(GameInitErrorCode error_code) {
  string exception_msg;

  exception_msg = string("There was an error initializing the Game!");
  exception_msg += " ";
  exception_msg += this->describeGameInitErrorCode(error_code);
  exception_msg += " ";
  exception_msg += this->describeGameInitErrorDetails(error_code);
  exception_msg += "\n";

  throw runtime_error(exception_msg);
}

int Game::verifySingletonProperty() {
  if (Game::instance == nullptr)
    return 0;
  else
    return -1;
};
