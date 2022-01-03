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
  OpenNewTextureErrorCode open_new_texture_error_code;
  OpenNewTextureStatusCode open_new_texture_status_code;

  this->cleanUpCurrentTexture();
  open_new_texture_status_code = this->openNewTexture(renderer, file);

  if(
    holds_alternative<OpenNewTextureErrorCode>(open_new_texture_status_code)
  ) {
    open_new_texture_error_code = get<OpenNewTextureErrorCode>(
      open_new_texture_status_code
    );
    this->handleOpenNewTextureError(open_new_texture_error_code);
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

void Sprite::cleanUpFailedOpenNewTexture(OpenNewTextureErrorCode error_code) {
  switch (error_code) {
    case OpenNewTextureErrorCode::ConfigureSpriteError:
      this->cleanUpCurrentTexture();
    case OpenNewTextureErrorCode::LoadTextureError:
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

string Sprite::describeOpenNewTextureErrorCode(
  OpenNewTextureErrorCode error_code
) {
  string description = string("This error was caused by ");
  
  switch (error_code) {
    case OpenNewTextureErrorCode::LoadTextureError:
      description += "attempting to load the texture from the file system";
      break;
    case OpenNewTextureErrorCode::ConfigureSpriteError:
      description += \
        "attempting to configure the sprite with the texture information";
      break;
  }

  description += ".";

  return description;
};

void Sprite::handleOpenNewTextureError(OpenNewTextureErrorCode error_code) {
  this->cleanUpFailedOpenNewTexture(error_code);
  this->throwOpenNewTextureException(error_code);
};

int Sprite::loadTexture(SDL_Renderer* renderer, string file) {
  this->texture = IMG_LoadTexture(renderer, file.c_str());
  
  if(this->texture != nullptr)
    return 0;

  else
    return -1;
};

OpenNewTextureStatusCode Sprite::openNewTexture(
  SDL_Renderer* renderer,
  string file
) {
  if(loadTexture(renderer, file) != 0)
    return OpenNewTextureErrorCode::LoadTextureError;
  
  if(configureSpriteWithTextureSpecification() != 0)
    return OpenNewTextureErrorCode::ConfigureSpriteError;

  return OpenNewTextureSuccessCode::OpenNewTextureSuccess;
};

void Sprite::throwOpenNewTextureException(OpenNewTextureErrorCode error_code) {
  string exception_msg;

  exception_msg = string("There was an error opening a texture!");
  exception_msg += " ";
  exception_msg += this->describeOpenNewTextureErrorCode(error_code);
  exception_msg += " More details: ";
  exception_msg += SDL_GetError();
  exception_msg += ".\n";

  throw runtime_error(exception_msg);
};
