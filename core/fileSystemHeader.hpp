#pragma once

#include "utils.hpp"

#define FS_NAME_SIZE 8

class FileSystemHeader final {
  public:
    void readInfo();

    void setMemoryStart(u8 *memory);

    char *getName();
    u32 getSize();
    u32 getChecksum();
    char *getVolumeName();
    FileSystemHeader() = delete;
    FileSystemHeader(u8 *memory);

  private:
    char name[FS_NAME_SIZE + 1];
    u32 size;
    u32 checksum;
    char *volumeName; // TODO: How to change this shitty leaked implementation ?
    u8 *memoryStart;
    u8 *currentMemory;

    void readName();
    void readSize();
    void readChecksum();
    void readVolumeName();
};