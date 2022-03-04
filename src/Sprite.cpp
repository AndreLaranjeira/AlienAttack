// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Sprite class - Source code.

// Class header include.
#include "Sprite.hpp"

// Class method implementations.
Sprite::Sprite(
  GameObject& associated
) : Component(associated, ComponentType::SpriteComponent) {};

Sprite::Sprite(
  GameObject& associated,
  SDL_Renderer* renderer,
  std::string file
) : Component(associated, ComponentType::SpriteComponent) {
  this->open(renderer, file);
};

// Public method implementations.
int Sprite::getHeight() const {
  return this->height;
};

int Sprite::getWidth() const {
  return this->width;
};

bool Sprite::isOpen() const {
  return (this->texture.get() != nullptr);
};

void Sprite::open(SDL_Renderer* renderer, std::string file) {
  try {
    this->loadAndConfigSprite(renderer, file);
  }
  catch(LoadAndConfigSpriteException& load_and_config_sprite_exception) {
    throw;
  }
};

void Sprite::render(SDL_Renderer* renderer) {
  SDL_Rect destination_rect = {
    .x = (int) this->associated.box.upper_left_corner.x,
    .y = (int) this->associated.box.upper_left_corner.y,
    .w = this->clip_rect.w,
    .h = this->clip_rect.h
  };

  SDL_RenderCopy(
    renderer,
    this->texture.get(),
    &this->clip_rect,
    &destination_rect
  );
};

void Sprite::setClip(int x_pos, int y_pos, int width, int height) {
  this->clip_rect.x = x_pos;
  this->clip_rect.y = y_pos;
  this->clip_rect.w = width;
  this->clip_rect.h = height;
};

void Sprite::update(double dt) {};

std::string LoadAndConfigSpriteErrorDescription::describeErrorCause(
  LoadAndConfigSpriteErrorCode error_code
) const {
  std::string error_cause = std::string("This error was caused by ");
  
  switch (error_code) {
    case LoadAndConfigSpriteErrorCode::LoadSpriteTextureError:
      error_cause += "attempting to load a sprite's texture from the file "
        "system";
      break;
    case LoadAndConfigSpriteErrorCode::ConfigureSpriteError:
      error_cause += "attempting to configure the sprite using the texture "
        "information";
      break;
  }

  error_cause += ".";

  return error_cause;
};

std::string LoadAndConfigSpriteErrorDescription::describeErrorDetails(
  LoadAndConfigSpriteErrorCode error_code
) const {
  std::string error_details;

  switch (error_code) {
    default:
      error_details += SDL_GetError();
  }

  error_details += ".";

  return error_details;
};

std::string LoadAndConfigSpriteErrorDescription::describeErrorSummary() const {
  std::string error_summary = std::string(
    "LoadAndConfigSpriteError: An error occurred when loading and configuring " 
    "a sprite!"
  );

  return error_summary;
};

// Private method implementations.
int Sprite::configSpriteWithTextureSpecs() {
  if(
    SDL_QueryTexture(
      this->texture.get(),
      nullptr,
      nullptr,
      &this->width,
      &this->height
    ) == 0
  ) {
    this->setClip(0, 0, this->width, this->height);
    this->associated.setDimensions(
      (double) this->width,
      (double) this->height
    );
    return 0;
  }
  else 
    return -1;
};

int Sprite::loadSpriteTexture(SDL_Renderer* renderer, std::string file) {
  this->texture.reset(IMG_LoadTexture(renderer, file.c_str()));
  
  if(this->texture.get() != nullptr)
    return 0;

  else
    return -1;
};

void Sprite::loadAndConfigSprite(
  SDL_Renderer* renderer,
  std::string file
) {
  if(loadSpriteTexture(renderer, file) != 0)
    throw LoadAndConfigSpriteException(
      LoadAndConfigSpriteErrorCode::LoadSpriteTextureError
    );
  
  if(configSpriteWithTextureSpecs() != 0)
    throw LoadAndConfigSpriteException(
      LoadAndConfigSpriteErrorCode::ConfigureSpriteError
    );
};
