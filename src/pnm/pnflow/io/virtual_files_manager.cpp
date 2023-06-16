#include <fstream>

#include "io/virtual_files_manager.h"

namespace io {

std::map<std::string, std::unique_ptr<std::stringstream>> VirtualFilesManager::stream_map_;

void VirtualFilesManager::Create(const std::string &name) {
    Write(name, "");
}

bool VirtualFilesManager::Exists(const std::string &name) {
    auto it = stream_map_.find(name);
    return it != stream_map_.end();
}

std::stringstream& VirtualFilesManager::Read(const std::string &name) {
    auto it = stream_map_.find(name);
    if (it != stream_map_.end()) {
        return *(it->second);
    } else {
        std::stringstream output;
        return output;
    }
}

void VirtualFilesManager::Read(const std::string &name, char *str_out, std::streamsize count) {
    std::string output;
    auto it = stream_map_.find(name);
    if (it != stream_map_.end()) {
        it->second->read(str_out, count);
    }
}

std::string VirtualFilesManager::ToString(const std::string &name) {
    auto it = stream_map_.find(name);
    if (it != stream_map_.end()) {
        return it->second->str();
    } else {
        return "";
    }
}

void VirtualFilesManager::Clear() {
    stream_map_.clear();
}

}  // namespace io
