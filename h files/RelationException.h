#pragma once
#include <string>
#include "LibraryException.h"

class RelationException : public LibraryException {
public:
    explicit RelationException(const std::string& message);
};
