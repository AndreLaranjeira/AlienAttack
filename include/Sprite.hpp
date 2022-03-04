// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Sprite class - Header file.

// Define guard.
#ifndef SPRITE_H_
#define SPRITE_H_

// Includes.
#include <memory>
#include <string>

// SDL2 includes.
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

// User includes.
#include "GameObject.hpp"

// Template includes.
#include "templates/ErrorDescription.hpp"
#include "templates/RuntimeException.hpp"

// Declarations.
enum LoadAndConfigSpriteErrorCode : unsigned short;
class LoadAndConfigSpriteErrorDescription;
class LoadAndConfigSpriteException;
class Sprite;

// Enumeration definitions.
enum LoadAndConfigSpriteErrorCode : unsigned short {
  LoadSpriteTextureError = 1,
  ConfigureSpriteError
};

// Type definitions.
using SDLTextureUniquePTR = \
  std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>;

// Auxiliary class definitions.
class LoadAndConfigSpriteErrorDescription :
  public ErrorDescription<LoadAndConfigSpriteErrorCode>
{
  // Public components.
  public:

    // Inherited methods.
    using ErrorDescription::ErrorDescription;

    // Method prototypes.
    std::string describeErrorCause(
      LoadAndConfigSpriteErrorCode error_code
    ) const override;
    std::string describeErrorDetails(
      LoadAndConfigSpriteErrorCode error_code
    ) const override;
    std::string describeErrorSummary() const override;
};

// Exception definitions.
class LoadAndConfigSpriteException :
  public RuntimeException<
    LoadAndConfigSpriteErrorCode,
    LoadAndConfigSpriteErrorDescription
  > {
  // Public components.
  public:

    // Inherited methods.
    using RuntimeException::RuntimeException;
};

// Class definition.
class Sprite : public Component {
  // Public components.
  public:

    // Class method prototypes.
    Sprite(GameObject& associated);
    Sprite(GameObject& associated, SDL_Renderer* renderer, std::string file);

    // Method prototypes.
    int getHeight() const;
    int getWidth() const;
    bool isOpen() const;
    void open(SDL_Renderer* renderer, std::string file);
    void render(SDL_Renderer* renderer) override;
    void setClip(int x_pos, int y_pos, int width, int height);
    void update(double dt) override;

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
    int configSpriteWithTextureSpecs();
    void loadAndConfigSprite(SDL_Renderer* renderer, std::string file);
    int loadSpriteTexture(SDL_Renderer* renderer, std::string file);
};

#endif // SPRITE_H_
