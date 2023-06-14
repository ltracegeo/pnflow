#ifndef _INPUT_INPUT_MANAGER_H_
#define _INPUT_INPUT_MANAGER_H_

#include <ios>
#include <map>
#include <memory>
#include <sstream>
#include <string>

namespace input {

class InputManager {
  public:
    static void WriteStream(const std::string &name, const char *content);
    static std::stringstream ReadStream(const std::string &name, std::ios_base::openmode mode = std::ios_base::in);

 private:
    static std::map<std::string, std::unique_ptr<std::stringstream>> stream_map_;
};

}  // namespace input

#endif  // _INPUT_INPUT_MANAGER_H_
