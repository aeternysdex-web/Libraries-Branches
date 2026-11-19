#include "ObjectNotFoundException.h"

ObjectNotFoundException::ObjectNotFoundException(const std::string& message)
    : LibraryException("Объект не найден: " + message) {}
