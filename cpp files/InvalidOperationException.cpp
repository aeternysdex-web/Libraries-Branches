#include "InvalidOperationException.h"

InvalidOperationException::InvalidOperationException(const std::string& message)
    : LibraryException("Недопустимая операция: " + message) {}
