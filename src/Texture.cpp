// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Texture class - Source code.

// Class header include.
#include "Texture.hpp"

// Class method implementations.
Texture::Texture(SDL_Renderer* renderer, std::string file) {
  this->open(renderer, file);
};

// Public method implementations.
std::string OpenTextureErrorDescription::describeErrorCause(
  OpenTextureErrorCode error_code
) const noexcept {
  std::string error_cause = std::string("This error was caused by ");
  
  switch (error_code) {
    case OpenTextureErrorCode::FailureToLoadTexture:
      error_cause += "attempting to load a texture from the file system";
      break;

    case OpenTextureErrorCode::BadTextureMetadata:
      error_cause += "unsuccessfully attempting to query a texture's metadata";
      break;
  }

  error_cause += ".";

  return error_cause;
};

std::string OpenTextureErrorDescription::describeErrorSummary() \
const noexcept {
  std::string error_summary = std::string(
    "OpenTextureError: An error occurred when opening a texture!"
  );

  return error_summary;
};

std::string RenderTextureErrorDescription::describeErrorCause(
  RenderTextureErrorCode error_code
) const noexcept {
  std::string error_cause = std::string("This error was caused by ");
  
  switch (error_code) {
    case RenderTextureErrorCode::RenderedUnopenedTexture:
      error_cause += "rendering a texture that was not opened";
      break;

    case RenderTextureErrorCode::FailureToRenderTexture:
      error_cause += "a failure to render a texture";
      break;
  }

  error_cause += ".";

  return error_cause;
};

std::string RenderTextureErrorDescription::describeErrorDetails(
  RenderTextureErrorCode error_code
) const noexcept {
  std::string error_details;

  switch (error_code) {
     case RenderTextureErrorCode::RenderedUnopenedTexture:
      error_details += "The texture to be rendered must have an open file "
        "pointer that is not NULL";
      break;

    case RenderTextureErrorCode::FailureToRenderTexture:
      error_details += SDL_GetError();
      break;
  }

  error_details += ".";

  return error_details;
};

std::string RenderTextureErrorDescription::describeErrorSummary() \
const noexcept {
  std::string error_summary = std::string(
    "RenderTextureError: An error occurred when rendering a texture!"
  );

  return error_summary;
};

int Texture::getHeight() const noexcept {
  return this->height;
};

int Texture::getWidth() const noexcept {
  return this->width;
};

bool Texture::isOpen() const noexcept {
  return (this->texture.get() != nullptr);
};

void Texture::open(SDL_Renderer* renderer, std::string file) {
  if(this->loadTextureFile(renderer, file) != 0)
    throw OpenTextureException(OpenTextureErrorCode::FailureToLoadTexture);

  if(this->extractTextureMetadata() != 0)
    throw OpenTextureException(
      OpenTextureErrorCode::BadTextureMetadata
    );
};

void Texture::render(
  SDL_Renderer* renderer,
  const VectorR2& destination
) const {
  SDL_Rect destination_rect = {
    .x = destination.xAsInt(),
    .y = destination.yAsInt(),
    .w = this->clip_rect.w,
    .h = this->clip_rect.h
  };

  if(!this->isOpen())
    throw RenderTextureException(
      RenderTextureErrorCode::RenderedUnopenedTexture
    );

  if(this->copyTextureToRenderTarget(renderer, destination_rect) != 0)
    throw RenderTextureException(
      RenderTextureErrorCode::FailureToRenderTexture
    );
};

void Texture::setClip(
  const VectorR2& upper_left_corner,
  int width,
  int height
) noexcept {
  this->clip_rect.x = upper_left_corner.xAsInt();
  this->clip_rect.y = upper_left_corner.yAsInt();
  this->clip_rect.w = width;
  this->clip_rect.h = height;
};

// Private method implementations.
int Texture::copyTextureToRenderTarget(
  SDL_Renderer* renderer,
  SDL_Rect& destination
) const noexcept {
  if(
    SDL_RenderCopy(
      renderer,
      this->texture.get(),
      &this->clip_rect,
      &destination
    ) != 0
  )
    return -1;

  return 0;
};

int Texture::extractTextureMetadata() noexcept {
  if(
    SDL_QueryTexture(
      this->texture.get(),
      nullptr,
      nullptr,
      &this->width,
      &this->height
    ) != 0
  )
    return -1;

  this->setClip(VectorR2(0, 0), this->width, this->height);
  return 0;
};

int Texture::loadTextureFile(
  SDL_Renderer* renderer,
  std::string file
) noexcept {
  this->texture.reset(IMG_LoadTexture(renderer, file.c_str()));
  
  if(this->texture)
    return 0;

  else
    return -1;
};
