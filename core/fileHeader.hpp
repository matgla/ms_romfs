#pragma once
#include <memory>
#include <string>

#include "utils.hpp"

enum class FileType {
    HARD_LINK,
    DIRECTORY,
    REGULAR_FILE,
    SYMBOLIC_LINK,
    BLOCK_DEVICE,
    CHAR_DEVICE,
    SOCKET,
    FIFO,
    NOT_EXIST
};

std::string getFileTypeString(const FileType &fileType);

class FileHeader final {
  public:
    FileHeader() = delete;
    FileHeader(u8 *memory);

    void readFile();
    void setMemoryStart(u8 *memory);

    u32 getNextFileOffset();
    u32 getAlignedNextFileOffset();
    u32 getSpecInfo();
    u32 getSize();
    u32 getChecksum();
    char *getName() const;

    void readNextFileOffset();
    void readFileType();
    void readSpecInfo();
    void readSize();
    void readChecksum();
    void readName();

    FileType getFileType();
    std::string getFileTypeString();
    bool isExist();

    u8 *getStartPtr();

  private:
    u32 nextFileHdr;
    u32 specInfo;
    u32 size;
    u32 checksum;
    u8 fileInfo;
    std::unique_ptr<char[]> name;
    u8 *memoryStart;
    u8 *currentMemory;
    u8 *dataStart;

    FileType fileType;
};