#include <cstdint>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <vector>

#include <romfs/romfs.hpp>

std::vector<uint8_t> readFileToMemory(std::string fileName)
{
    std::ifstream file(fileName, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        throw std::runtime_error("Can't open file: " + fileName);
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> buffer(size);
    file.read((char *)buffer.data(), size);

    return buffer;
}

int main()
{
    std::vector<uint8_t> memory;
    memory = readFileToMemory("example_volume.romfs");
    romfs::RomFsDisk disk(memory.data());

    std::cout << "Shell like program for testing romfs. Available commands: [ls, cd, cat]" << std::endl;
    auto directory = disk.get_directory("/");
    while (true)
    {
        std::string command = "";
        std::string path = "";
        std::string command_line;
        std::getline(std::cin, command_line);

        if (command_line.find(" ") != std::string::npos)
        {
            command = command_line.substr(0, command_line.find(" "));
            path = command_line.substr(command_line.find(" "), command_line.size());
            if (path.find_last_of(" ") != std::string::npos)
            {
                path = path.substr(path.find_last_of(" ") + 1, path.size());
            }
        }
        else
        {
            command = command_line;
        }

        std::cout << "> " << command << " " << path << std::endl;

        if (command == "q" || command == "exit")
        {
            std::cout << "exiting..." << std::endl;
            return 0;
        }

        if (command == "cd")
        {
            if (!path.size())
            {
                std::cout << "Path to directory not provided" << std::endl;
                continue;
            }
            if (path[0] != '/')
            {
                directory = directory->get_directory(path);
            }
            else
            {
                directory = disk.get_directory(path);
            }

            if (!directory)
            {
                std::cout << "Path not exists: " << path << std::endl;
                continue;
            }
        }

        if (command == "ls")
        {
            std::optional<romfs::Directory> listed_directory = directory;

            if (path.size())
            {
                if (path[0] != '/')
                {
                    listed_directory = directory->get_directory(path);
                }
                else
                {
                    listed_directory = disk.get_directory(path);
                }
            }
            if (!listed_directory)
            {
                std::cout << "Path not exists: " << path << std::endl;
                continue;
            }

            for (const auto& file : *listed_directory)
            {
                std::cout << std::right << std::setw(8) << std::dec << file.get_size() << " "
                    << to_string(file.get_file_type()) << " 0x" << std::hex << file.get_specinfo()
                    << " " << std::left << std::setw(20) << file.get_name() << std::endl;
            }
        }

        if (command == "cat")
        {
            if (!path.size())
            {
                std::cout << "Path to file not provided" << std::endl;
                continue;
            }

            auto file = directory->get_file(path);

            if (!file)
            {
                std::cout << "File not exists: " << path << std::endl;
                continue;
            }

            std::string_view data(reinterpret_cast<const char*>(file->data()), file->size());
            std::cout << "size: " << file->size() << std::endl;

            for (const char c : data)
            {
                std::cout << c;
            }
            std::cout << std::endl;
        }
    }


    return 0;
}
