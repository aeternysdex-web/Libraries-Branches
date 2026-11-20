#include "OutOfRangeException.h"

OutOfRangeException::OutOfRangeException(const std::string& message)
    : LibraryException("Выход за пределы диапазона: " + message) {}
