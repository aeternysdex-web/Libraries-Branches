#include "RelationException.h"

RelationException::RelationException(const std::string& message)
    : LibraryException("Нарушение связи: " + message) {}
