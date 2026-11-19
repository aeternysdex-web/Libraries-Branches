#pragma once
#include <string>
#include "LibraryException.h"

class ObjectNotFoundException : public LibraryException {
public:
    explicit ObjectNotFoundException(const std::string& message);
};
