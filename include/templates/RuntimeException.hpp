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

// Namespace.
using namespace std;

// Class definition.
template <typename TErrorCode, class TErrorDescription>
class RuntimeException : public TErrorDescription, public runtime_error {
  // Construction pre-requisites.
  static_assert(
    is_base_of<ErrorDescription<TErrorCode>, TErrorDescription>::value,
    "TErrorDescription must be derived from ErrorDescription template."
  );

  // Public components.
  public:

    // Class method prototypes.
    RuntimeException(TErrorCode error_code);
};

// Class method implementations.
template <typename TErrorCode, class TErrorDescription>
RuntimeException<TErrorCode,TErrorDescription>::RuntimeException(
  TErrorCode error_code
) :
  TErrorDescription(error_code),
  runtime_error(this->describeError(error_code)) {};

#endif // RUNTIME_EXCEPTION_T_
