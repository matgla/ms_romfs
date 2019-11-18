#include "fileSystemHeader.hpp"
#include "fileHelper.hpp"
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

TEST_F(filesystem_fixture, readFileSystemHeader) {
    auto fileSystemInfo = FileSystemHeader(disk.data());

    u32 expectedFileSytemSize = 376752;
    EXPECT_EQ(expectedFileSytemSize, fileSystemInfo.get_volume_size());

    uint32_t expectedFileSystemHeaderSize = 32;
    EXPECT_EQ(expectedFileSystemHeaderSize, fileSystemInfo.get_header_size());

    u32 expectedChecksum = 3579543322;
    EXPECT_EQ(expectedChecksum, fileSystemInfo.get_checksum());

    std::string volumeName(fileSystemInfo.get_volume_name());
    EXPECT_EQ("JADYMY", volumeName);
}