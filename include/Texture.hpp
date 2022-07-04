// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Texture class - Header file.

// Define guard.
#ifndef TEXTURE_H_
#define TEXTURE_H_

// Includes.
#include <memory>
#include <string>

// SDL2 includes.
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

// User includes.
#include "VectorR2.hpp"

// Template includes.
#include "templates/ErrorDescription.hpp"
#include "templates/RuntimeException.hpp"

// Declarations.
enum OpenTextureErrorCode : unsigned short;
enum RenderTextureErrorCode : unsigned short;
class OpenTextureErrorDescription;
class OpenTextureException;
class Texture;

// Enumeration definitions.
enum OpenTextureErrorCode : unsigned short {
  FailureToLoadTexture = 1,
  BadTextureMetadata
};

enum RenderTextureErrorCode : unsigned short {
  RenderedUnopenedTexture = 1,
  FailureToRenderTexture
};

// Type definitions.
using SDLTextureUniquePTR = \
  std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>;

// Auxiliary class definitions.
class OpenTextureErrorDescription :
  public ErrorDescription<OpenTextureErrorCode>
{
  // Public components.
  public:

    // Inherited methods.
    using ErrorDescription::ErrorDescription;

    // Method prototypes.
    std::string describeErrorCause(
      OpenTextureErrorCode error_code
    ) const noexcept override;
    std::string describeErrorSummary() const noexcept override;
};

class RenderTextureErrorDescription :
  public ErrorDescription<RenderTextureErrorCode>
{
  // Public components.
  public:

    // Inherited methods.
    using ErrorDescription::ErrorDescription;

    // Method prototypes.
    std::string describeErrorCause(
      RenderTextureErrorCode error_code
    ) const noexcept override;
    std::string describeErrorDetails(
      RenderTextureErrorCode error_code
    ) const noexcept override;
    std::string describeErrorSummary() const noexcept override;
};

// Exception definitions.
class OpenTextureException :
  public RuntimeException<OpenTextureErrorCode, OpenTextureErrorDescription>
{
  // Public components.
  public:

    // Inherited methods.
    using RuntimeException::RuntimeException;
};

class RenderTextureException :
  public RuntimeException<
    RenderTextureErrorCode,
    RenderTextureErrorDescription
  >
{
  // Public components.
  public:

    // Inherited methods.
    using RuntimeException::RuntimeException;
};

// Class definition.
class Texture {
  // Public components.
  public:

    // Class method prototypes.
    Texture() noexcept = default;
    Texture(SDL_Renderer* renderer, std::string file);

    // Method prototypes.
    int getHeight() const noexcept;
    int getWidth() const noexcept;
    bool isOpen() const noexcept;
    void open(SDL_Renderer* renderer, std::string file);
    void render(
      SDL_Renderer* renderer,
      const VectorR2& destination
    ) const;
    void setClip(
      const VectorR2& upper_left_corner,
      int width,
      int height
    ) noexcept;

  // Private components.
  private:

    // Members.
    SDL_Rect clip_rect;
    int height = 0;
    SDLTextureUniquePTR texture = SDLTextureUniquePTR(
      nullptr,
      &SDL_DestroyTexture
    );
    int width = 0;

    // Method prototypes.
    int copyTextureToRenderTarget(
      SDL_Renderer* renderer,
      SDL_Rect& destination
    ) const noexcept;
    int extractTextureMetadata() noexcept;
    int loadTextureFile(SDL_Renderer* renderer, std::string file) noexcept;
};

#endif // TEXTURE_H_
