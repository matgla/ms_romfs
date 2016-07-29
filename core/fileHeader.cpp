#include "fileHeader.hpp"
#include <cstring>
#include <iomanip>
#include <iostream>
#include <stdexcept>

std::string FileHeader::getFileTypeString() {
    switch (fileType) {
    case FileType::BLOCK_DEVICE: {
        return "b";
    } break;
    case FileType::CHAR_DEVICE: {
        return "c";
    } break;
    case FileType::DIRECTORY: {
        return "d";
    } break;
    case FileType::FIFO: {
        return "fi";
    } break;
    case FileType::HARD_LINK: {
        return "h";
    } break;
    case FileType::REGULAR_FILE: {
        return "f";
    } break;
    case FileType::SOCKET: {
        return "s";
    } break;
    case FileType::SYMBOLIC_LINK: {
        return "l";
    } break;
    }
}

FileHeader::FileHeader(u8 *memory)
    : nextFileHdr(0), specInfo(0), size(0), checksum(0), name(nullptr),
      memoryStart(memory), currentMemory(memory), dataStart(nullptr),
      fileType(FileType::NOT_EXIST) {
}

void FileHeader::readFile() {
    readNextFileOffset();
    readFileType();
    readSpecInfo();
    readSize();
    readChecksum();
    readName();
}

void FileHeader::setMemoryStart(u8 *memory) {
    memoryStart = memory;
    currentMemory = memory;
}

u32 FileHeader::getNextFileOffset() {
    return nextFileHdr;
}

u32 FileHeader::getAlignedNextFileOffset() {
    return nextFileHdr;
}

u32 FileHeader::getSpecInfo() {
    return specInfo;
}

u32 FileHeader::getSize() {
    return size;
}

u32 FileHeader::getChecksum() {
    return checksum;
}

char *FileHeader::getName() const {
    return name.get();
}

void FileHeader::readNextFileOffset() {
    u32 data = read32(&currentMemory);
    nextFileHdr = data & 0xfffffff0;
    fileInfo = data & 0x00000007;
}

void FileHeader::readFileType() {
    std::cout << std::to_string(fileInfo) << std::endl;
    switch (fileInfo) {
    case 0: {
        fileType = FileType::HARD_LINK;
    } break;
    case 1: {
        fileType = FileType::DIRECTORY;
    } break;
    case 2: {
        fileType = FileType::REGULAR_FILE;
    } break;
    case 3: {
        fileType = FileType::SYMBOLIC_LINK;
    } break;
    case 4: {
        fileType = FileType::BLOCK_DEVICE;
    } break;
    case 5: {
        fileType = FileType::CHAR_DEVICE;
    } break;
    case 6: {
        fileType = FileType::SOCKET;
    } break;
    case 7: {
        fileType = FileType::FIFO;
    } break;
    default: { fileType = FileType::NOT_EXIST; }
    }
}

void FileHeader::readSpecInfo() {
    specInfo = read32(&currentMemory);
}

void FileHeader::readSize() {
    size = read32(&currentMemory);
}

void FileHeader::readChecksum() {
    checksum = read32(&currentMemory);
}

void FileHeader::readName() {
    u32 size = 0;
    size = strlen((char *)(currentMemory));

    name.reset(new char[size]);
    char *volumeNamePtr = name.get();

    readString(&volumeNamePtr, &currentMemory);
}

FileType FileHeader::getFileType() {
    return fileType;
}

bool FileHeader::isExist() {
    if (fileType == FileType::NOT_EXIST) {
        return false;
    }
    return true;
}

u8 *FileHeader::getStartPtr() {
    return memoryStart;
}