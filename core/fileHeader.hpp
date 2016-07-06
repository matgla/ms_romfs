#pragma once
#include <memory>

#include "utils.hpp"

class FileHeader final {
  public:
    FileHeader() = delete;
    FileHeader(u8 *memory);

    void readFile();
    void setMemoryStart(u8 *memory);

    u32 getNextFileOffset();
    u32 getSpecInfo();
    u32 getSize();
    u32 getChecksum();
    char *getName() const;

    void readNextFileOffset();
    void readSpecInfo();
    void readSize();
    void readChecksum();
    void readName();

  private:
    u32 nextFileHdr;
    u32 specInfo;
    u32 size;
    u32 checksum;
    std::unique_ptr<char[]> name;
    u8 *memoryStart;
    u8 *currentMemory;
    u8 *dataStart;
};