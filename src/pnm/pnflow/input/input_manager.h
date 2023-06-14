#ifndef _INPUT_INPUT_MANAGER_H_
#define _INPUT_INPUT_MANAGER_H_

#include <map>
#include <memory>
#include <sstream>
#include <string>

class InputManager {
  public:
    static void WriteStream(const char *name, const char *content);
    static std::stringstream ReadStream(const char *name);

 private:
    static std::map<std::string, std::unique_ptr<std::stringstream>> stream_map_;
};

#endif  // _INPUT_INPUT_MANAGER_H_