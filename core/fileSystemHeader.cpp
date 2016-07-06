#include "fileSystemHeader.hpp"
#include <cstring>

FileSystemHeader::FileSystemHeader(u8 *memory)
    : memoryStart(makeAlignedPtr(memory, 16)),
      currentMemory(makeAlignedPtr(memory, 16)), size(0), checksum(0),
      volumeName(nullptr), endHeader(nullptr) {
}

void FileSystemHeader::readInfo() {
    readName();
    readSize();
    readChecksum();
    readVolumeName();
    endHeader = currentMemory;
}

void FileSystemHeader::readName() {
    memcpy(name, currentMemory, FS_NAME_SIZE);
    name[FS_NAME_SIZE] = 0;
    currentMemory += FS_NAME_SIZE;
}

void FileSystemHeader::readSize() {
    size = read32(&currentMemory);
}

void FileSystemHeader::readChecksum() {
    checksum = read32(&currentMemory);
}

void FileSystemHeader::readVolumeName() {
    u32 size = 0;
    size = strlen((char *)(currentMemory));

    volumeName.reset(new char[size]);
    char *volumeNamePtr = volumeName.get();

    readString(&volumeNamePtr, &currentMemory);
}

char *FileSystemHeader::getName() {
    return name;
}

u32 FileSystemHeader::getSize() {
    return size;
}

u32 FileSystemHeader::getChecksum() {
    return checksum;
}

char *FileSystemHeader::getVolumeName() {
    return volumeName.get();
}

u8 *FileSystemHeader::getHeaderEnd() {
    return endHeader;
}

void FileSystemHeader::setMemoryStart(u8 *memory) {
    memoryStart = makeAlignedPtr(memory, 16);
    currentMemory = makeAlignedPtr(memory, 16);
}
