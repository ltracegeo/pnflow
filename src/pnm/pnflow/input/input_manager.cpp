#include "input/input_manager.h"

void InputManager::WriteStream(const char *name, const char *content) {
    stream_map_.emplace(name, std::make_unique<std::stringstream>(content))
}

std::stringstream InputManager::ReadStream(const char *name) {
    return *(stream_map_.at(name));
}
