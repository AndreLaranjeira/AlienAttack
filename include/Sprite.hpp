// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Sprite class - Header file.

// Define guard.
#ifndef SPRITE_H_
#define SPRITE_H_

// Includes.
#include <memory>
#include <stdexcept>
#include <string>

// SDL2 includes.
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

// Template includes.
#include "templates/ErrorDescription.hpp"

// Namespace.
using namespace std;

// Enumeration definitions.
enum OpenNewTextureErrorCode {
  LoadTextureError = 1,
  ConfigureSpriteError
};

// Type definitions.
using SDLTextureUniquePTR = \
  unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>;

// Auxiliary class definitions.
class OpenNewTextureErrorDescription :
  public ErrorDescriptionTemplate<OpenNewTextureErrorCode>
{
  // Public components.
  public:

    // Inherited methods.
    using ErrorDescriptionTemplate::ErrorDescriptionTemplate;

    // Method prototypes.
    string describeErrorCause(OpenNewTextureErrorCode error_code) override;
    string describeErrorDetails(OpenNewTextureErrorCode error_code) override;
    string describeErrorSummary() override;
};

// Exception definitions.
class OpenNewTextureException :
  public OpenNewTextureErrorDescription,
  public runtime_error
{
  // Public components.
  public:

    // Class method prototypes.
    OpenNewTextureException(OpenNewTextureErrorCode error_code);
};

// Class definition.
class Sprite {
  // Public components.
  public:

    // Class method prototypes.
    Sprite() = default;
    Sprite(SDL_Renderer* renderer, string file);

    // Method prototypes.
    int getHeight();
    int getWidth();
    bool isOpen();
    void open(SDL_Renderer* renderer, string file);
    void render(SDL_Renderer* renderer, int x_pos, int y_pos);
    void setClip(int x_pos, int y_pos, int width, int height);

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
    int configureSpriteWithTextureSpecification();
    string describeOpenNewTextureErrorCode(OpenNewTextureErrorCode error_code);
    int loadTexture(SDL_Renderer* renderer, string file);
    void openNewTexture(SDL_Renderer* renderer, string file);
};

#endif // SPRITE_H_