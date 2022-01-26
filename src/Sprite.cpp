// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Sprite class - Source code.

// Class header include.
#include "Sprite.hpp"

// Class method implementations.
Sprite::Sprite(SDL_Renderer* renderer, string file) {
  this->open(renderer, file);
};

OpenNewTextureException::OpenNewTextureException(
  OpenNewTextureErrorCode error_code
) :
  OpenNewTextureErrorDescription(error_code),
  runtime_error(this->describeError(error_code)) {};

// Public method implementations.
int Sprite::getHeight() {
  return this->height;
};

int Sprite::getWidth() {
  return this->width;
};

bool Sprite::isOpen() {
  return (this->texture.get() != nullptr);
};

void Sprite::open(SDL_Renderer* renderer, string file) {
  try {
    this->openNewTexture(renderer, file);
  }
  catch(OpenNewTextureException& open_new_texture_exception) {
    throw;
  }
};

void Sprite::render(SDL_Renderer* renderer, int x_pos, int y_pos) {
  SDL_Rect destination_rect = {
    .x = x_pos,
    .y = y_pos,
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

string OpenNewTextureErrorDescription::describeErrorCause(
  OpenNewTextureErrorCode error_code
) {
  string error_cause = string("This error was caused by ");
  
  switch (error_code) {
    case OpenNewTextureErrorCode::LoadTextureError:
      error_cause += "attempting to load the texture from the file system";
      break;
    case OpenNewTextureErrorCode::ConfigureSpriteError:
      error_cause += "attempting to configure the sprite with the texture "
        "information";
      break;
  }

  error_cause += ".";

  return error_cause;
};

string OpenNewTextureErrorDescription::describeErrorDetails(
  OpenNewTextureErrorCode error_code
) {
  string error_details;

  switch (error_code) {
    default:
      error_details += SDL_GetError();
  }

  error_details += ".";

  return error_details;
};

string OpenNewTextureErrorDescription::describeErrorSummary() {
  string error_summary = string(
    "OpenNewTextureError: There was an error opening a texture!"
  );

  return error_summary;
};

// Private method implementations.
int Sprite::configureSpriteWithTextureSpecification() {
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
    return 0;
  }
  else {
    return -1;
  }
};

int Sprite::loadTexture(SDL_Renderer* renderer, string file) {
  this->texture.reset(IMG_LoadTexture(renderer, file.c_str()));
  
  if(this->texture.get() != nullptr)
    return 0;

  else
    return -1;
};

void Sprite::openNewTexture(
  SDL_Renderer* renderer,
  string file
) {
  if(loadTexture(renderer, file) != 0)
    throw OpenNewTextureException(OpenNewTextureErrorCode::LoadTextureError);
  
  if(configureSpriteWithTextureSpecification() != 0)
    throw OpenNewTextureException(
      OpenNewTextureErrorCode::ConfigureSpriteError
    );
};
