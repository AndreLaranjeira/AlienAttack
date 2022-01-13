// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Error Description Template class - Template file.

// Define guard.
#ifndef ERROR_DESCRIPTION_TEMPLATE_H_
#define ERROR_DESCRIPTION_TEMPLATE_H_

// Includes.
#include <string>

// Namespace.
using namespace std;

// Class definition.
template <class TErrorCode>
class ErrorDescriptionTemplate {
  // Public components.
  public:

    // Class method prototypes.
    ErrorDescriptionTemplate(TErrorCode error_code);
    ~ErrorDescriptionTemplate();

    // Method prototypes.
    TErrorCode getErrorCode();

    // Virtual method prototypes.
    virtual string describeErrorCause(TErrorCode error_code) = 0;
    virtual string describeErrorDetails(TErrorCode error_code) = 0;
    virtual string describeErrorSummary() = 0;

  // Protected components.
  protected:

    // Method prototypes.
    string describeError(TErrorCode error_code);

  // Private components.
  private:

    // Members.
    TErrorCode error_code;
};

// Class method implementations.
template <class TErrorCode>
ErrorDescriptionTemplate<TErrorCode>::ErrorDescriptionTemplate(
  TErrorCode error_code
) :
  error_code(error_code) {};

template <class TErrorCode>
ErrorDescriptionTemplate<TErrorCode>::~ErrorDescriptionTemplate() {};

// Public method implementations.
template <class TErrorCode>
TErrorCode ErrorDescriptionTemplate<TErrorCode>::getErrorCode() {
  return this->error_code;
};

// Protected method implementations.
template <class TErrorCode>
string ErrorDescriptionTemplate<TErrorCode>::describeError(
  TErrorCode error_code
) {
  string error_description;

  error_description = this->describeErrorSummary();
  error_description += " ";
  error_description += this->describeErrorCause(error_code);
  error_description += " ";
  error_description += "More details: ";
  error_description += this->describeErrorDetails(error_code);
  error_description += "\n";

  return error_description;
};

#endif // ERROR_DESCRIPTION_TEMPLATE_H_