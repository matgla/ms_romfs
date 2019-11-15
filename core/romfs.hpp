#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <string_view>

#include "file.hpp"
#include "fileHeader.hpp"
#include "fileSystemHeader.hpp"
#include "utils.hpp"

class RomFsDisk
{
public:
    RomFsDisk(uint8_t* memory);
    File openFile(const std::string_view& fileName);

    FileSystemHeader fileSystemHeader;
    std::vector<std::string>
    getAllFileNamesInDir(const std::string &directoryPath);
    FileHeader findFileHeaderIntoDir(u8 *directoryStart,
                                     const std::string &fileName);

  private:
    bool getFileOffsetToFirstFileIntoDir(u32 directoryFirstFileOffset,
                                         const std::string &dirName);

    uint8_t* memory_start_;
    uint8_t* firstFileHeader;
};
