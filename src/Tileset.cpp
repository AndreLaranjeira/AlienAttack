// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Tileset class - Source code.

// Class header include.
#include "Tileset.hpp"

// Class method implementations.
Tileset::Tileset(
  std::string file,
  SDL_Renderer* renderer,
  unsigned int tile_width,
  unsigned int tile_height
) :
  tileset(renderer, file),
  tile_height(tile_height),
  tile_width(tile_width)
{
  this->measureTilesetDimensions();
};

// Public method implementations.
std::string MeasureTilesetDimensionsErrorDescription::describeErrorCause(
  MeasureTilesetDimensionsErrorCode error_code
) const noexcept {
  std::string error_cause = std::string("This error was caused by ");
  
  switch (error_code) {
    case MeasureTilesetDimensionsErrorCode::InvalidColumnMeasurementError:
      error_cause += "an invalid column measurement for the tileset";
      break;
    case MeasureTilesetDimensionsErrorCode::InvalidRowMeasurementError:
      error_cause += "an invalid row measurement for the tileset";
      break;
  }

  error_cause += ".";

  return error_cause;
};

std::string MeasureTilesetDimensionsErrorDescription::describeErrorDetails(
  MeasureTilesetDimensionsErrorCode error_code
) const noexcept {
  std::string error_details;

  switch (error_code) {
    case MeasureTilesetDimensionsErrorCode::InvalidColumnMeasurementError:
      error_details += "The tileset width must be divisible by the specified "
        "tile width to ensure a whole number of columns";
      break;
    case MeasureTilesetDimensionsErrorCode::InvalidRowMeasurementError:
      error_details += "The tileset height must be divisible by the specified "
        "tile height to ensure a whole number of rows";
      break;
  }

  error_details += ".";

  return error_details;
};

std::string MeasureTilesetDimensionsErrorDescription::describeErrorSummary() \
const noexcept {
  std::string error_summary = std::string(
    "MeasureTilesetDimensionsError: An error occurred when measuring the "
      "dimensions of a tileset!"
  );

  return error_summary;
};

std::string RenderTileErrorDescription::describeErrorCause(
  RenderTileErrorCode error_code
) const noexcept {
  std::string error_cause = std::string("This error was caused by ");
  
  switch (error_code) {
    case RenderTileErrorCode::InexistantTileIndexError:
      error_cause += "attempting to render a tile at an inexistant index in "
        "the tileset";
      break;
    case RenderTileErrorCode::FailureToRenderTileError:
      error_cause += "an error at rendering a tile from the tileset";
      break;
  }

  error_cause += ".";

  return error_cause;
};

std::string RenderTileErrorDescription::describeErrorDetails(
  RenderTileErrorCode error_code
) const noexcept {
  std::string error_details;

  switch (error_code) {
    case RenderTileErrorCode::InexistantTileIndexError:
      error_details += "The tile index to be rendered must exist in the "
        "tileset. Please use the Tileset::tileExistsAtIndex method";
      break;
    case RenderTileErrorCode::FailureToRenderTileError:
      error_details += SDL_GetError();
      break;
  }

  error_details += ".";

  return error_details;
};

std::string RenderTileErrorDescription::describeErrorSummary() const noexcept {
  std::string error_summary = std::string(
    "RenderTileError: An error occurred when rendering a tile from a tileset!"
  );

  return error_summary;
};

unsigned int Tileset::getTileHeight() const noexcept {
  return this->tile_height;
};

unsigned int Tileset::getTileWidth() const noexcept {
  return this->tile_width;
};

void Tileset::renderTile(
  unsigned int requested_tile_index,
  SDL_Renderer* renderer,
  const VectorR2& destination
) {
  if(!this->tileExistsAtIndex(requested_tile_index))
    throw RenderTileException(RenderTileErrorCode::InexistantTileIndexError);

  if(this->index_of_last_tile_rendered != requested_tile_index)
    this->setTilesetClipForTileAtIndex(requested_tile_index);

  try {
    this->tileset.render(renderer, destination);
  }
  catch(RenderTextureException& render_texture_exception) {
    throw RenderTileException(RenderTileErrorCode::FailureToRenderTileError);
  }
};

bool Tileset::tileExistsAtIndex(unsigned int tile_index) const noexcept {
  return tile_index < this->number_of_tiles_in_tileset;
};

// Private method implementations.
int Tileset::measureNumberOfColumnsInTileset() noexcept {
  unsigned int tileset_width = this->tileset.getWidth();

  if(tileset_width % this->tile_width != 0)
    return -1;

  this->columns = tileset_width / this->tile_width;
  return 0;
};

int Tileset::measureNumberOfRowsInTileset() noexcept {
  unsigned int tileset_height = this->tileset.getHeight();

  if(tileset_height % this->tile_height != 0)
    return -1;

  this->rows = tileset_height / this->tile_height;
  return 0;
};

void Tileset::measureTilesetDimensions() {
  if(this->measureNumberOfColumnsInTileset() != 0)
    throw MeasureTilesetDimensionsException(
      MeasureTilesetDimensionsErrorCode::InvalidColumnMeasurementError
    );

  if(this->measureNumberOfRowsInTileset() != 0)
    throw MeasureTilesetDimensionsException(
      MeasureTilesetDimensionsErrorCode::InvalidRowMeasurementError
    );

  this->number_of_tiles_in_tileset = (this->rows * this->columns);
};

void Tileset::setTilesetClipForTileAtIndex(unsigned int tile_index) noexcept {
  this->tileset.setClip(
    this->upperLeftCornerOfTileAtIndex(tile_index),
    this->tile_width,
    this->tile_height
  );
  this->index_of_last_tile_rendered = tile_index;
};

VectorR2 Tileset::upperLeftCornerOfTileAtIndex(
  unsigned int tile_index
) const noexcept {
  return VectorR2(
    (tile_index % this->columns) * this->tile_width,
    ((unsigned int) (tile_index / this->columns)) * this->tile_height
  );
};
