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

    auto fileStart = disk.data() + fileSystemInfo.get_header_size();
    auto fileHeader = FileHeader(fileStart);

    EXPECT_EQ(64, fileHeader.get_next_file_offset());
    EXPECT_EQ(32, fileHeader.get_specinfo());
    EXPECT_EQ(0, fileHeader.get_size());
    EXPECT_EQ(3523215255, fileHeader.get_checksum());
    EXPECT_EQ(FileType::DIRECTORY, fileHeader.get_file_type());

    std::string name(fileHeader.get_name());

    EXPECT_EQ(".", name);

    u32 offset = fileHeader.get_next_file_offset();
    if (offset % 16) {
        offset = offset - (offset % 16); // align to uint32_t
    }

    fileStart = disk.data() + offset;
    fileHeader = FileHeader(fileStart);

    EXPECT_EQ(96, fileHeader.get_next_file_offset());
    EXPECT_EQ(32, fileHeader.get_specinfo());
    EXPECT_EQ(0, fileHeader.get_size());
    EXPECT_EQ(3520200576, fileHeader.get_checksum());
    EXPECT_EQ(FileType::HARD_LINK, fileHeader.get_file_type());

    EXPECT_EQ("..", fileHeader.get_name());

    offset = fileHeader.get_next_file_offset();
    if (offset % 16) {
        offset = offset - (offset % 16); // align to uint32_t
    }

    fileStart = disk.data() + offset;
    fileHeader = FileHeader(fileStart);

    EXPECT_EQ(12320, fileHeader.get_next_file_offset());
    EXPECT_EQ(0, fileHeader.get_specinfo());
    EXPECT_EQ(12182, fileHeader.get_size());
    EXPECT_EQ(1989521158, fileHeader.get_checksum());
    EXPECT_EQ(FileType::REGULAR_FILE, fileHeader.get_file_type());

    EXPECT_EQ("CMakeCache.txt", fileHeader.get_name());

    offset = fileHeader.get_next_file_offset();
    if (offset % 16) {
        offset = offset - (offset % 16); // align to uint32_t
    }

    fileStart = disk.data() + offset;
    fileHeader = FileHeader(fileStart);

    EXPECT_EQ(13184, fileHeader.get_next_file_offset());
    EXPECT_EQ(12352, fileHeader.get_specinfo());
    EXPECT_EQ(0, fileHeader.get_size());
    EXPECT_EQ(2526099767, fileHeader.get_checksum());
    EXPECT_EQ(FileType::DIRECTORY, fileHeader.get_file_type());

    EXPECT_EQ("inc", fileHeader.get_name());

    offset = fileHeader.get_next_file_offset();
    if (offset % 16) {
        offset = offset - (offset % 16); // align to uint32_t
    }

    fileStart = disk.data() + offset;
    fileHeader = FileHeader(fileStart);

    EXPECT_EQ(66528, fileHeader.get_next_file_offset());
    EXPECT_EQ(13216, fileHeader.get_specinfo());
    EXPECT_EQ(0, fileHeader.get_size());
    EXPECT_EQ(3516358403, fileHeader.get_checksum());
    EXPECT_EQ(FileType::DIRECTORY, fileHeader.get_file_type());

    EXPECT_EQ(".git", fileHeader.get_name());
}