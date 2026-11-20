#pragma once
#include <string>
#include "LibraryException.h"

class OutOfRangeException : public LibraryException {
public:
    explicit OutOfRangeException(const std::string& message);
};
