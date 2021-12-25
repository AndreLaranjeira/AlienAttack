// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Sprite class - Source code.

// Class header include.
#include "Sprite.hpp"

// Class method implementations.
Sprite::Sprite() {};

Sprite::Sprite(SDL_Renderer* renderer, string file) {
  this->open(renderer, file);
};

Sprite::~Sprite() {
  this->cleanUpCurrentTexture();
};

// Public method implementations.
int Sprite::getHeight() {
  return this->height;
};

int Sprite::getWidth() {
  return this->width;
};

bool Sprite::isOpen() {
  return (this->texture != nullptr);
};

void Sprite::open(SDL_Renderer* renderer, string file) {
  OpenTextureErrorCode open_texture_error_code;
  OpenTextureStatusCode open_texture_status_code;

  this->cleanUpCurrentTexture();
  open_texture_status_code = this->openTexture(renderer, file);

  if(holds_alternative<OpenTextureErrorCode>(open_texture_status_code)) {
    open_texture_error_code = get<OpenTextureErrorCode>(
      open_texture_status_code
    );
    this->handleOpenTextureError(open_texture_error_code);
  }
};

void Sprite::render(SDL_Renderer* renderer, int x_pos, int y_pos) {
  SDL_Rect destination_rect = {
    .x = x_pos,
    .y = y_pos,
    .w = this->clip_rect.w,
    .h = this->clip_rect.h
  };

  SDL_RenderCopy(renderer, this->texture, &this->clip_rect, &destination_rect);
};

void Sprite::setClip(int x_pos, int y_pos, int width, int height) {
  this->clip_rect.x = x_pos;
  this->clip_rect.y = y_pos;
  this->clip_rect.w = width;
  this->clip_rect.h = height;
};

// Private method implementations.
void Sprite::cleanUpCurrentTexture() {
  if(this->isOpen()) {
    SDL_DestroyTexture(this->texture);
    this->texture = nullptr;
  }
};

void Sprite::cleanUpFailedOpenTexture(OpenTextureErrorCode error_code) {
  switch (error_code) {
    case OpenTextureErrorCode::ConfigureSpriteError:
      this->cleanUpCurrentTexture();
    case OpenTextureErrorCode::LoadTextureError:
      ;
  }
};

int Sprite::configureSpriteWithTextureSpecification() {
  if(
    SDL_QueryTexture(
      this->texture,
      nullptr,
      nullptr,
      &this->width,
      &this->height
    ) == 0
  ) {
    this->setClip(0, 0, this->width, this->height);
    return 0;
  }
  else {
    return -1;
  }
};

string Sprite::describeOpenTextureErrorCode(OpenTextureErrorCode error_code) {
  string description = string("This error was caused by ");
  
  switch (error_code) {
    case OpenTextureErrorCode::LoadTextureError:
      description += "attempting to load the texture from the file system";
      break;
    case OpenTextureErrorCode::ConfigureSpriteError:
      description += \
        "attempting to configure the sprite with the texture information";
      break;
  }

  description += ".";

  return description;
};

void Sprite::handleOpenTextureError(OpenTextureErrorCode error_code) {
  this->cleanUpFailedOpenTexture(error_code);
  this->throwOpenTextureException(error_code);
};

int Sprite::loadTexture(SDL_Renderer* renderer, string file) {
  this->texture = IMG_LoadTexture(renderer, file.c_str());
  
  if(this->texture != nullptr)
    return 0;

  else
    return -1;
};

OpenTextureStatusCode Sprite::openTexture(
  SDL_Renderer* renderer,
  string file
) {
  if(loadTexture(renderer, file) != 0)
    return OpenTextureErrorCode::LoadTextureError;
  
  if(configureSpriteWithTextureSpecification() != 0)
    return OpenTextureErrorCode::ConfigureSpriteError;

  return OpenTextureSuccessCode::OpenTextureSuccess;
};

void Sprite::throwOpenTextureException(OpenTextureErrorCode error_code) {
  string exception_msg;

  exception_msg = string("There was an error opening a texture!");
  exception_msg += " ";
  exception_msg += this->describeOpenTextureErrorCode(error_code);
  exception_msg += " More details: ";
  exception_msg += SDL_GetError();
  exception_msg += ".\n";

  throw runtime_error(exception_msg);
};
