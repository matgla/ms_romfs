#include "utils.hpp"
#include <cstring>


u32 read32(u8 **fp) {
    u32 decodedNumber = **fp << 24 | *(++*fp) << 16 | *(++*fp) << 8 | *(++*fp);
    ++*fp;
    return decodedNumber;
}

u32 readString(char **str, u8 **fp) {
    u32 size = 0;
    size = strlen(reinterpret_cast<char *>(*fp));

    if (size % 4) {
        size = size + 4 - (size % 4); // align to 4 bytes
    }
    size += 4;
    strcpy(*str, reinterpret_cast<char *>(*fp));
    *fp += size + 4;

    return size;
}

std::vector<std::string> getFilesArray(std::string filePath) {
    std::vector<std::string> files;
    if (0 == filePath.length()) {
        return files;
    }
    int prevSlashPosition = 1, nextSlashPosition = 1;
    while ((nextSlashPosition = filePath.find("/", prevSlashPosition)) !=
           std::string::npos) {
        auto fileName = filePath.substr(prevSlashPosition,
                                        nextSlashPosition - prevSlashPosition);
        if (0 != fileName.length()) {
            files.push_back(fileName);
        }

        prevSlashPosition = ++nextSlashPosition;
    }
    auto fileName = filePath.substr(prevSlashPosition,
                                    nextSlashPosition - prevSlashPosition);
    if (0 != fileName.length()) {
        files.push_back(fileName);
    }
    return files;
}