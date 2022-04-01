// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Runtime Exception class - Template file.

// Define guard.
#ifndef RUNTIME_EXCEPTION_T_
#define RUNTIME_EXCEPTION_T_

// Includes.
#include <stdexcept>
#include <string>

// Template includes.
#include "../templates/ErrorDescription.hpp"

// Declarations.
template <typename TErrorCode, class TErrorDescription> class RuntimeException;

// Class definition.
template <typename TErrorCode, class TErrorDescription>
class RuntimeException : public TErrorDescription, public std::runtime_error {
  // Construction pre-requisites.
  static_assert(
    std::is_base_of<ErrorDescription<TErrorCode>, TErrorDescription>::value,
    "TErrorDescription must be derived from ErrorDescription template."
  );

  // Public components.
  public:

    // Class method prototypes.
    RuntimeException(TErrorCode error_code);

    // Method prototypes.
    TErrorCode getErrorCode() const noexcept;

  // Private components.
  private:

    // Members.
    TErrorCode error_code;
};

// Class method implementations.
template <typename TErrorCode, class TErrorDescription>
RuntimeException<TErrorCode, TErrorDescription>::RuntimeException(
  TErrorCode error_code
) :
  TErrorDescription(),
  runtime_error(this->describeError(error_code)),
  error_code(error_code) {};

// Public method implementations.
template <typename TErrorCode, class TErrorDescription>
TErrorCode RuntimeException<TErrorCode, TErrorDescription>::getErrorCode() \
const noexcept {
  return this->error_code;
};

#endif // RUNTIME_EXCEPTION_T_
