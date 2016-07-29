#include "romfs.hpp"
#include <fstream>
#include <iostream>
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

int main() {
    std::vector<u8> memory;
    memory = readFileToMemory("test_img.romfs");
    RomFsDisk disk(memory.data());
    auto files = disk.getAllFileNamesInDir("/inc");
    for (const auto &fileName : files) {
        std::cout << fileName << std::endl;
    }
    auto file = disk.openFile("/inc/romfs.h");

    return 0;
}