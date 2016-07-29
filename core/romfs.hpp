#pragma once

#include <string>
#include <vector>

#include "file.hpp"
#include "fileHeader.hpp"
#include "fileSystemHeader.hpp"
#include "utils.hpp"

class RomFsDisk {
    u8 *fileStart;
    u8 *firstFileHeader;

  public:
    RomFsDisk(u8 *file);
    File openFile(const std::string &fileName);
    FileSystemHeader fileSystemHeader;
    std::vector<std::string>
    getAllFileNamesInDir(const std::string &directoryPath);
    FileHeader findFileHeaderIntoDir(u8 *directoryStart,
                                     const std::string &fileName);

  private:
    bool getFileOffsetToFirstFileIntoDir(u32 directoryFirstFileOffset,
                                         const std::string &dirName);
};
