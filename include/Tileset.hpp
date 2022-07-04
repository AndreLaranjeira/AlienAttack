// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Tileset class - Header file.

// Define guard.
#ifndef TILESET_H_
#define TILESET_H_

// Includes.
#include <string>

// SDL2 includes.
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>

// User includes.
#include "Texture.hpp"
#include "VectorR2.hpp"

// Template includes.
#include "templates/ErrorDescription.hpp"
#include "templates/RuntimeException.hpp"

// Declarations.
enum MeasureTilesetDimensionsErrorCode : unsigned short;
class MeasureTilesetDimensionsErrorDescription;
class MeasureTilesetDimensionsException;
enum RenderTileErrorCode : unsigned short;
class RenderTileErrorDescription;
class RenderTileException;
class Tileset;

// Enumeration definitions.
enum MeasureTilesetDimensionsErrorCode : unsigned short {
  InvalidColumnMeasurement = 1,
  InvalidRowMeasurement
};

enum RenderTileErrorCode : unsigned short {
  OutOfRangeTileIndex = 1,
  FailureToRenderTile
};

// Auxiliary class definitions.
class MeasureTilesetDimensionsErrorDescription :
  public ErrorDescription<MeasureTilesetDimensionsErrorCode>
{
  // Public components.
  public:

    // Inherited methods.
    using ErrorDescription::ErrorDescription;

    // Method prototypes.
    std::string describeErrorCause(
      MeasureTilesetDimensionsErrorCode error_code
    ) const noexcept override;
    std::string describeErrorDetails(
      MeasureTilesetDimensionsErrorCode error_code
    ) const noexcept override;
    std::string describeErrorSummary() const noexcept override;
};

class RenderTileErrorDescription :
  public ErrorDescription<RenderTileErrorCode>
{
  // Public components.
  public:

    // Inherited methods.
    using ErrorDescription::ErrorDescription;

    // Method prototypes.  
    std::string describeErrorCause(
      RenderTileErrorCode error_code
    ) const noexcept override;
    std::string describeErrorDetails(
      RenderTileErrorCode error_code
    ) const noexcept override;
    std::string describeErrorSummary() const noexcept override;
};

// Exception definitions.
class MeasureTilesetDimensionsException :
  public RuntimeException<
    MeasureTilesetDimensionsErrorCode,
    MeasureTilesetDimensionsErrorDescription
  >
{
  // Public components.
  public:

    // Inherited methods.
    using RuntimeException::RuntimeException;
};

class RenderTileException :
  public RuntimeException<RenderTileErrorCode, RenderTileErrorDescription>
{
  // Public components.
  public:

    // Inherited methods.
    using RuntimeException::RuntimeException;
};

// Class definition.
class Tileset {
  // Public components.
  public:

    // Class method prototypes.
    Tileset(
      std::string file,
      SDL_Renderer* renderer,
      unsigned int tile_width,
      unsigned int tile_height
    );

    // Method prototypes.
    unsigned int getNumberOfTiles() const noexcept;
    unsigned int getTileHeight() const noexcept;
    unsigned int getTileWidth() const noexcept;
    void renderTile(
      unsigned int requested_tile_index,
      SDL_Renderer* renderer,
      const VectorR2& destination
    );

  // Private components.
  private:

    // Members.
    unsigned int columns;
    unsigned int index_of_last_tile_rendered = -1;
    unsigned int number_of_tiles_in_tileset;
    unsigned int rows;
    Texture tileset;
    unsigned int tile_height;
    unsigned int tile_width;

    // Method prototypes.
    int measureNumberOfColumnsInTileset() noexcept;
    int measureNumberOfRowsInTileset() noexcept;
    void measureTilesetDimensions();
    void setTilesetClipForTileAtIndex(unsigned int tile_index) noexcept;
    bool tileExistsAtIndex(unsigned int tile_index) const noexcept;
    VectorR2 upperLeftCornerOfTileAtIndex(
      unsigned int tile_index
    ) const noexcept;
};

#endif // TILESET_H_
