// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Runtime Exception Template class - Template file.

// Define guard.
#ifndef RUNTIME_EXCEPTION_TEMPLATE_H_
#define RUNTIME_EXCEPTION_TEMPLATE_H_

// Includes.
#include <stdexcept>
#include <string>

// Template includes.
#include "../templates/ErrorDescription.hpp"

// Namespace.
using namespace std;

// Class definition.
template <typename TErrorCode, class TErrorDescription>
class RuntimeExceptionTemplate :
  public TErrorDescription,
  public runtime_error
{
  // Construction pre-requisites.
  static_assert(
    is_base_of<ErrorDescriptionTemplate<TErrorCode>, TErrorDescription>::value,
    "TErrorDescription must be derived from ErrorDescriptionTemplate."
  );

  // Public components.
  public:

    // Class method prototypes.
    RuntimeExceptionTemplate(TErrorCode error_code);
};

// Class method implementations.
template <typename TErrorCode, class TErrorDescription>
RuntimeExceptionTemplate<
  TErrorCode,
  TErrorDescription
>::RuntimeExceptionTemplate(TErrorCode error_code) :
  TErrorDescription(error_code),
  runtime_error(this->describeError(error_code)) {};

#endif // RUNTIME_EXCEPTION_TEMPLATE_H_
