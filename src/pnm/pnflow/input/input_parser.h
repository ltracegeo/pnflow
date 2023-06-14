#ifndef _INPUT_PARSER_H_
#define _INPUT_PARSER_H_

#include <string>

namespace input {

class InputParser {
  public:
    InputParser(const std::string &input_config);

    std::string GetNetworkName();

  private:
    std::string input_config_;
};

}  // namespace input

#endif  // _INPUT_PARSER_H_