#pragma once
#include <string>
#include "LibraryException.h"

class InvalidDataException : public LibraryException {
public:
    explicit InvalidDataException(const std::string& message);
};
