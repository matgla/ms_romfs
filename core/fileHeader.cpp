#include <cstring>

#include "fileHeader.hpp"

FileHeader::FileHeader(u8 *memory)
    : nextFileHdr(0), specInfo(0), size(0), checksum(0), name(nullptr),
      memoryStart(memory), currentMemory(memory), dataStart(nullptr) {
}

void FileHeader::readFile() {
    readNextFileOffset();
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
    nextFileHdr = read32(&currentMemory);
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