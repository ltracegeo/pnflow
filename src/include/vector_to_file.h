#include <iostream>
#include <fstream>
#include <vector>

void writeVectorToFile(const std::vector<double>& myVector, const std::string& filename,
                       const std::string& columnTitle = "") {
    std::ofstream outputFile(filename);

    if (!outputFile) {
        std::cerr << "Error: Unable to open file for writing!" << std::endl;
        return;
    }

    if (!columnTitle.empty()) {
        outputFile << columnTitle << "\n";
    }

    for (auto& value : myVector) {
        outputFile << value << "\n";
    }

    outputFile.close();
}
