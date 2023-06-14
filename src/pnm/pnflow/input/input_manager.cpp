#include <fstream>

#include "input/input_manager.h"

namespace input {

std::map<std::string, std::unique_ptr<std::stringstream>> InputManager::stream_map_;

void InputManager::WriteStream(const std::string &name, const char *content) {
    stream_map_.emplace(name, std::make_unique<std::stringstream>(content));
}

std::stringstream InputManager::ReadStream(const std::string &name, std::ios_base::openmode mode) {
    std::stringstream output;
    try {
        output << stream_map_.at(name)->rdbuf();
    } catch(...) {
        std::ifstream file_stream;
        file_stream.open(name, mode);
        output << file_stream.rdbuf();
        file_stream.close();
    }
    return output;
}

}  // namespace input
