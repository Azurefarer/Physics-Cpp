#ifndef GL_CORE_RIGIDBODY_H_
#define GL_CORE_RIGIDBODY_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Function to read the contents of a file into a string
std::string read_file(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Function to convert GLSL code into C++ std::string literals
std::string GLSL_to_string(const std::string& glslCode) {
    std::stringstream input(glslCode);
    std::stringstream output;
    std::string line;

    while (std::getline(input, line)) {
        // Trim leading and trailing whitespace
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        if (!line.empty()) {
            size_t start = line.find("uniform ");
            if (start != std::string::npos) {
                // Extract uniform name
                size_t nameStart = line.find_last_of(' ') + 1;
                size_t nameEnd = line.find(';');
                std::string uniformName = line.substr(nameStart, nameEnd - nameStart);

                // Generate C++ string
                output << "const std::string " << uniformName << " = \"" << line << "\";\n";
            }
        }
    }

    return output.str();
}

#endif