#include "input/input_parser.h"

#include <regex>

namespace input {

InputParser::InputParser(const std::string &input_config)
        : input_config_(input_config) {}

std::string InputParser::GetNetworkName() {
    std::regex expression(R"(NETWORK\s+([FT])\s+(\S+)\s*;)");
    std::smatch match;
    if (std::regex_search(input_config_, match, expression)) {
        return match[2];
    } else {
        return "";
    }
}

std::string InputParser::GetTitle() {
    std::regex expression(R"(TITLE\s+(\S+)\s*;)");
    std::smatch match;
    if (std::regex_search(input_config_, match, expression)) {
        return match[1];
    } else {
        return "";
    }
}

}  // namespace input
