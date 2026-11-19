#include "LibraryException.h"

LibraryException::LibraryException(const std::string& message)
    : std::runtime_error(message) {}
