#include "fileHeader.hpp"
#include "fileHelper.hpp"
#include "fileSystemHeader.hpp"
#include "utils.hpp"
#include "gtest/gtest.h"

#include <string>
#include <vector>

class filesystem_fixture : public ::testing::Test {
  protected:
    std::vector<u8> disk;
    virtual void SetUp() {
        disk = readFileToMemory("test_img.romfs");
    };
};

TEST_F(filesystem_fixture, readFileHeader) {
    auto fileSystemInfo = FileSystemHeader(disk.data());

    auto fileStart = const_cast<uint8_t*>(fileSystemInfo.getHeaderEnd());
    auto fileHeader = FileHeader(fileStart);
    fileHeader.readFile();

    EXPECT_EQ(64, fileHeader.getNextFileOffset());
    EXPECT_EQ(32, fileHeader.getSpecInfo());
    EXPECT_EQ(0, fileHeader.getSize());
    EXPECT_EQ(3523215255, fileHeader.getChecksum());
    EXPECT_EQ(FileType::DIRECTORY, fileHeader.getFileType());

    std::string name = fileHeader.getName();

    EXPECT_EQ(".", name);

    u32 offset = fileHeader.getNextFileOffset();
    if (offset % 16) {
        offset = offset - (offset % 16); // align to uint32_t
    }

    fileStart = disk.data() + offset;
    fileHeader = FileHeader(fileStart);
    fileHeader.readFile();

    EXPECT_EQ(96, fileHeader.getNextFileOffset());
    EXPECT_EQ(32, fileHeader.getSpecInfo());
    EXPECT_EQ(0, fileHeader.getSize());
    EXPECT_EQ(3520200576, fileHeader.getChecksum());
    EXPECT_EQ(FileType::HARD_LINK, fileHeader.getFileType());

    name = fileHeader.getName();

    EXPECT_EQ("..", name);

    offset = fileHeader.getNextFileOffset();
    if (offset % 16) {
        offset = offset - (offset % 16); // align to uint32_t
    }

    fileStart = disk.data() + offset;
    fileHeader = FileHeader(fileStart);
    fileHeader.readFile();

    EXPECT_EQ(12320, fileHeader.getNextFileOffset());
    EXPECT_EQ(0, fileHeader.getSpecInfo());
    EXPECT_EQ(12182, fileHeader.getSize());
    EXPECT_EQ(1989521158, fileHeader.getChecksum());
    EXPECT_EQ(FileType::REGULAR_FILE, fileHeader.getFileType());

    name = fileHeader.getName();

    EXPECT_EQ("CMakeCache.txt", name);

    offset = fileHeader.getNextFileOffset();
    if (offset % 16) {
        offset = offset - (offset % 16); // align to uint32_t
    }

    fileStart = disk.data() + offset;
    fileHeader = FileHeader(fileStart);
    fileHeader.readFile();

    EXPECT_EQ(13184, fileHeader.getNextFileOffset());
    EXPECT_EQ(12352, fileHeader.getSpecInfo());
    EXPECT_EQ(0, fileHeader.getSize());
    EXPECT_EQ(2526099767, fileHeader.getChecksum());
    EXPECT_EQ(FileType::DIRECTORY, fileHeader.getFileType());

    name = fileHeader.getName();

    EXPECT_EQ("inc", name);

    offset = fileHeader.getNextFileOffset();
    if (offset % 16) {
        offset = offset - (offset % 16); // align to uint32_t
    }

    fileStart = disk.data() + offset;
    fileHeader = FileHeader(fileStart);
    fileHeader.readFile();

    EXPECT_EQ(66528, fileHeader.getNextFileOffset());
    EXPECT_EQ(13216, fileHeader.getSpecInfo());
    EXPECT_EQ(0, fileHeader.getSize());
    EXPECT_EQ(3516358403, fileHeader.getChecksum());
    EXPECT_EQ(FileType::DIRECTORY, fileHeader.getFileType());

    name = fileHeader.getName();

    EXPECT_EQ(".git", name);
}