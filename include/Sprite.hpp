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
enum OpenTextureErrorCode {
  LoadTextureError = 1,
  ConfigureSpriteError
};

enum OpenTextureSuccessCode {
  OpenTextureSuccess
};

// Type definitions.
using OpenTextureStatusCode = \
  variant<OpenTextureSuccessCode, OpenTextureErrorCode>;

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
    int height;
    SDL_Texture* texture = nullptr;
    int width;

    // Method prototypes.
    void cleanUpCurrentTexture();
    void cleanUpFailedOpenTexture(OpenTextureErrorCode error_code);
    int configureSpriteWithTextureSpecification();
    string describeOpenTextureErrorCode(OpenTextureErrorCode error_code);
    void handleOpenTextureError(OpenTextureErrorCode error_code);
    int loadTexture(SDL_Renderer* renderer, string file);
    OpenTextureStatusCode openTexture(SDL_Renderer* renderer, string file);
    void throwOpenTextureException(OpenTextureErrorCode error_code);
};

#endif // SPRITE_H_