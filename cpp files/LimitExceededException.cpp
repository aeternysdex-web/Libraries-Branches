#include "LimitExceededException.h"

LimitExceededException::LimitExceededException(const std::string& message)
    : LibraryException("Превышено ограничение: " + message) {}
