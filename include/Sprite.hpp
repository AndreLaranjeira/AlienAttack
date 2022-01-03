// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Sprite class - Header file.

// Define guard.
#ifndef SPRITE_H_
#define SPRITE_H_

// Includes.
#include <iostream>
#include <stdexcept>
#include <string>
#include <variant>

// SDL2 includes.
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

// Namespace.
using namespace std;

// Enumeration definitions.
enum OpenNewTextureErrorCode {
  LoadTextureError = 1,
  ConfigureSpriteError
};

enum OpenNewTextureSuccessCode {
  OpenNewTextureSuccess
};

// Type definitions.
using OpenNewTextureStatusCode = \
  variant<OpenNewTextureSuccessCode, OpenNewTextureErrorCode>;

// Class definition.
class Sprite {
  // Public components.
  public:

    // Class method prototypes.
    Sprite();
    Sprite(SDL_Renderer* renderer, string file);
    ~Sprite();

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
    SDL_Texture* texture = nullptr;
    int width = 0;

    // Method prototypes.
    void cleanUpCurrentTexture();
    void cleanUpFailedOpenNewTexture(OpenNewTextureErrorCode error_code);
    int configureSpriteWithTextureSpecification();
    string describeOpenNewTextureErrorCode(OpenNewTextureErrorCode error_code);
    void handleOpenNewTextureError(OpenNewTextureErrorCode error_code);
    int loadTexture(SDL_Renderer* renderer, string file);
    OpenNewTextureStatusCode openNewTexture(SDL_Renderer* renderer, string file);
    void throwOpenNewTextureException(OpenNewTextureErrorCode error_code);
};

#endif // SPRITE_H_