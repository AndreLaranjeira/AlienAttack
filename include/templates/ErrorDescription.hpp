// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Error Description class - Template file.

// Define guard.
#ifndef ERROR_DESCRIPTION_T_
#define ERROR_DESCRIPTION_T_

// Includes.
#include <string>

// SDL2 includes.
#include <SDL2/SDL_error.h>

// Declarations.
template <typename TErrorCode> class ErrorDescription;

// Class definition.
template <typename TErrorCode>
class ErrorDescription {
  // Public components.
  public:

    // Virtual method prototypes.
    virtual std::string describeErrorCause(
      TErrorCode error_code
    ) const noexcept = 0;
    virtual std::string describeErrorDetails(
      TErrorCode error_code
    ) const noexcept;
    virtual std::string describeErrorSummary() const noexcept = 0;

  // Protected components.
  protected:

    // Method prototypes.
    std::string describeError(TErrorCode error_code) const noexcept;
};

// Public method implementations.
template <typename TErrorCode>
std::string ErrorDescription<TErrorCode>::describeErrorDetails(
  TErrorCode error_code
) const noexcept {
  std::string error_details = std::string(SDL_GetError()).append(".");

  return error_details;
};

// Protected method implementations.
template <typename TErrorCode>
std::string ErrorDescription<TErrorCode>::describeError(
  TErrorCode error_code
) const noexcept {
  std::string error_description;

  error_description = this->describeErrorSummary();
  error_description += " ";
  error_description += this->describeErrorCause(error_code);
  error_description += " ";
  error_description += "More details: ";
  error_description += this->describeErrorDetails(error_code);
  error_description += "\n";

  return error_description;
};

#endif // ERROR_DESCRIPTION_T_
