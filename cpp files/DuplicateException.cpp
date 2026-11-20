#include "DuplicateException.h"

DuplicateException::DuplicateException(const std::string& message)
    : LibraryException("Дублирование ID: " + message) {}
