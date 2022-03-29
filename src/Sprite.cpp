// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Sprite class - Source code.

// Class header include.
#include "Sprite.hpp"

// Class method implementations.
Sprite::Sprite(
  GameObject& associated
) : Component(associated, ComponentType::SpriteComponent) {
  this->attachToAssociatedGameObject();
};

Sprite::Sprite(
  GameObject& associated,
  SDL_Renderer* renderer,
  std::string file
) : Component(associated, ComponentType::SpriteComponent) {
  this->open(renderer, file);
  this->attachToAssociatedGameObject();
};

// Public method implementations.
std::string OpenSpriteErrorDescription::describeErrorCause(
  OpenSpriteErrorCode error_code
) const noexcept {
  std::string error_cause = std::string("This error was caused by ");
  
  switch (error_code) {
    case OpenSpriteErrorCode::LoadSpriteTextureError:
      error_cause += "attempting to load a sprite's texture from the file "
        "system";
      break;
    case OpenSpriteErrorCode::ConfigureSpriteError:
      error_cause += "attempting to configure the sprite using the texture "
        "information";
      break;
  }

  error_cause += ".";

  return error_cause;
};

std::string OpenSpriteErrorDescription::describeErrorDetails(
  OpenSpriteErrorCode error_code
) const noexcept {
  std::string error_details;

  switch (error_code) {
    default:
      error_details += SDL_GetError();
  }

  error_details += ".";

  return error_details;
};

std::string OpenSpriteErrorDescription::describeErrorSummary() const noexcept {
  std::string error_summary = std::string(
    "OpenSpriteError: An error occurred when opening a sprite!"
  );

  return error_summary;
};

int Sprite::getHeight() const noexcept {
  return this->height;
};

int Sprite::getWidth() const noexcept {
  return this->width;
};

bool Sprite::isOpen() const noexcept {
  return (this->texture.get() != nullptr);
};

void Sprite::open(SDL_Renderer* renderer, std::string file) {
  if(loadSpriteTexture(renderer, file) != 0)
    throw OpenSpriteException(OpenSpriteErrorCode::LoadSpriteTextureError);
  
  if(configSpriteWithTextureSpecs() != 0)
    throw OpenSpriteException(OpenSpriteErrorCode::ConfigureSpriteError);
};

void Sprite::render(SDL_Renderer* renderer) noexcept {
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

void Sprite::setClip(int x_pos, int y_pos, int width, int height) noexcept {
  this->clip_rect.x = x_pos;
  this->clip_rect.y = y_pos;
  this->clip_rect.w = width;
  this->clip_rect.h = height;
};

void Sprite::update(double dt) noexcept {};

// Private method implementations.
int Sprite::configSpriteWithTextureSpecs() noexcept {
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

int Sprite::loadSpriteTexture(
  SDL_Renderer* renderer,
  std::string file
) noexcept {
  this->texture.reset(IMG_LoadTexture(renderer, file.c_str()));
  
  if(this->texture.get() != nullptr)
    return 0;

  else
    return -1;
};
