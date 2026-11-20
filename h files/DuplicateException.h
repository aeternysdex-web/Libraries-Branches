#pragma once
#include <string>
#include "LibraryException.h"

class DuplicateException : public LibraryException {
public:
    explicit DuplicateException(const std::string& message);
};
