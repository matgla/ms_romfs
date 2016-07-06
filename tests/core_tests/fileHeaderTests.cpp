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
    auto fileSystemInfo = FileSystemHeader(nullptr);
    fileSystemInfo.setMemoryStart(disk.data());
    fileSystemInfo.readInfo();

    auto fileStart = fileSystemInfo.getHeaderEnd();
    auto fileHeader = FileHeader(fileStart);
    fileHeader.readFile();

    EXPECT_EQ(73, fileHeader.getNextFileOffset());
    EXPECT_EQ(32, fileHeader.getSpecInfo());
    EXPECT_EQ(0, fileHeader.getSize());
    EXPECT_EQ(3523215255, fileHeader.getChecksum());

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

    name = fileHeader.getName();

    EXPECT_EQ("..", name);

    offset = fileHeader.getNextFileOffset();
    if (offset % 16) {
        offset = offset - (offset % 16); // align to uint32_t
    }

    fileStart = disk.data() + offset;
    fileHeader = FileHeader(fileStart);
    fileHeader.readFile();

    EXPECT_EQ(12322, fileHeader.getNextFileOffset());
    EXPECT_EQ(0, fileHeader.getSpecInfo());
    EXPECT_EQ(12182, fileHeader.getSize());
    EXPECT_EQ(1989521158, fileHeader.getChecksum());

    name = fileHeader.getName();

    EXPECT_EQ("CMakeCache.txt", name);

    offset = fileHeader.getNextFileOffset();
    if (offset % 16) {
        offset = offset - (offset % 16); // align to uint32_t
    }

    fileStart = disk.data() + offset;
    fileHeader = FileHeader(fileStart);
    fileHeader.readFile();

    EXPECT_EQ(13193, fileHeader.getNextFileOffset());
    EXPECT_EQ(12352, fileHeader.getSpecInfo());
    EXPECT_EQ(0, fileHeader.getSize());
    EXPECT_EQ(2526099767, fileHeader.getChecksum());

    name = fileHeader.getName();

    EXPECT_EQ("inc", name);

    offset = fileHeader.getNextFileOffset();
    if (offset % 16) {
        offset = offset - (offset % 16); // align to uint32_t
    }

    fileStart = disk.data() + offset;
    fileHeader = FileHeader(fileStart);
    fileHeader.readFile();

    EXPECT_EQ(66537, fileHeader.getNextFileOffset());
    EXPECT_EQ(13216, fileHeader.getSpecInfo());
    EXPECT_EQ(0, fileHeader.getSize());
    EXPECT_EQ(3516358403, fileHeader.getChecksum());

    name = fileHeader.getName();

    EXPECT_EQ(".git", name);
}