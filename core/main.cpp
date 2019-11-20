#include "romfs.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <iomanip>

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
    memory = readFileToMemory("example_volume.romfs");
    RomFsDisk disk(memory.data());

    std::cerr << "ls /" << std::endl;

    std::string command = "";
    while (command != "q")
    {
        std::cin >> command;

        auto directory = disk.get_directory(command);
        if (!directory)
        {
            std::cout << "Path not exists: " << command << std::endl;
            continue;
        }

        for (const auto& file : *directory)
        {
            std::cout << std::right << std::setw(8) << std::dec << file.get_size() << " " << to_string(file.get_file_type()) << " 0x" << std::hex << file.get_specinfo() << " " << file.get_name() << std::endl;
        }
    }


    return 0;
}
