#include "fileHelper.hpp"

#include <fstream>
#include <stdexcept>

std::vector<u8> readFileToMemory(std::string fileName) {
    std::ifstream file(fileName, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        throw std::runtime_error("Can't open file: " + fileName);
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<u8> buffer(size);
    file.read((char *)buffer.data(), size);

    return buffer;
}