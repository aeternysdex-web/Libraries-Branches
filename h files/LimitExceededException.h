#pragma once
#include <string>
#include "LibraryException.h"

class LimitExceededException : public LibraryException {
public:
    explicit LimitExceededException(const std::string& message);
};
