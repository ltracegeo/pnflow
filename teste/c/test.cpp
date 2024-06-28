#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

extern "C" {
#include "pnflow.h"
}

std::string ReadFile(const std::string &file_path) {
    std::ifstream t(file_path);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

int main() {
    std::string config = ReadFile("input.txt");
    std::string link1 = ReadFile("Image_link1.dat");
    std::string link2 = ReadFile("Image_link2.dat");
    std::string node1 = ReadFile("Image_node1.dat");
    std::string node2 = ReadFile("Image_node2.dat");

    std::string result = pnflow(config.c_str(), link1.c_str(), link2.c_str(), node1.c_str(), node2.c_str());
    return 0;
}
