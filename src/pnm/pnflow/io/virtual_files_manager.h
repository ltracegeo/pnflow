#ifndef _IO_VIRTUAL_FILES_MANAGER_H_
#define _IO_VIRTUAL_FILES_MANAGER_H_

#include <ios>
#include <map>
#include <memory>
#include <sstream>
#include <string>

namespace io {

class VirtualFilesManager {
  public:
    static void Create(const std::string &name);

    static bool Exists(const std::string &name);

    template<class T>
    static void Write(const std::string &name, T &value) {
        auto it = stream_map_.find(name);
        if (it == stream_map_.end()) {
            auto result = stream_map_.emplace(name, std::make_unique<std::stringstream>());
            if (result.second) {
                auto new_it = result.first;
                *(new_it->second) << value;
            }
        } else {
           *(it->second) << value;
        }
    }

    static std::string ToString(const std::string &name);

    static void Clear();

 private:
    static std::map<std::string, std::unique_ptr<std::stringstream>> stream_map_;
};

}  // namespace io

#endif  // _IO_VIRTUAL_FILES_MANAGER_H_
