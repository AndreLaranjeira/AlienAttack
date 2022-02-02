// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Error Description class - Template file.

// Define guard.
#ifndef ERROR_DESCRIPTION_T_
#define ERROR_DESCRIPTION_T_

// Includes.
#include <string>

// Namespace.
using namespace std;

// Class definition.
template <typename TErrorCode>
class ErrorDescription {
  // Public components.
  public:

    // Class method prototypes.
    ErrorDescription(TErrorCode error_code);

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
template <typename TErrorCode>
ErrorDescription<TErrorCode>::ErrorDescription(TErrorCode error_code) :
  error_code(error_code) {};

// Public method implementations.
template <typename TErrorCode>
TErrorCode ErrorDescription<TErrorCode>::getErrorCode() {
  return this->error_code;
};

// Protected method implementations.
template <typename TErrorCode>
string ErrorDescription<TErrorCode>::describeError(TErrorCode error_code) {
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

#endif // ERROR_DESCRIPTION_T_
