#include "InvalidDataException.h"

InvalidDataException::InvalidDataException(const std::string& message)
    : LibraryException("Некорректные данные: " + message) {}
