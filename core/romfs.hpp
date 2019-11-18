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
    RomFsDisk(const uint8_t* memory);
    // File openFile(const std::string_view& fileName);

    std::vector<std::string>
    getAllFileNamesInDir(const std::string &directoryPath);
    FileHeader findFileHeaderIntoDir(u8 *directoryStart,
                                     const std::string &fileName);

  private:
    FileHeader get_first_file_header() const;
    bool getFileOffsetToFirstFileIntoDir(u32 directoryFirstFileOffset,
                                         const std::string &dirName);

    const uint8_t* memory_start_;
    FileSystemHeader file_system_header_;
};
