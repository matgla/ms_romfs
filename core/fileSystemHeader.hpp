#pragma once

#include "utils.hpp"
#include <memory>

#define FS_NAME_SIZE 8

class FileSystemHeader final {
  public:
    FileSystemHeader() = delete;
    FileSystemHeader(u8 *memory);

    void readInfo();
    void setMemoryStart(u8 *memory);

    char *getName();
    u32 getSize();
    u32 getChecksum();
    char *getVolumeName();

    u8 *getHeaderEnd();

  private:
    char name[FS_NAME_SIZE + 1];
    u32 size;
    u32 checksum;
    std::unique_ptr<char[]> volumeName;
    u8 *memoryStart;
    u8 *currentMemory;
    u8 *endHeader;

    void readName();
    void readSize();
    void readChecksum();
    void readVolumeName();
};