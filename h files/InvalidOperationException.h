#pragma once
#include <string>
#include "LibraryException.h"

class InvalidOperationException : public LibraryException {
public:
    explicit InvalidOperationException(const std::string& message);
};
