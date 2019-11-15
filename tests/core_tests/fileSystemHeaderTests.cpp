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
    EXPECT_EQ(expectedFileSytemSize, fileSystemInfo.getSize());

    u32 expectedChecksum = 3579543322;
    EXPECT_EQ(expectedChecksum, fileSystemInfo.getChecksum());

    std::string volumeName = fileSystemInfo.getVolumeName();
    EXPECT_EQ("JADYMY", volumeName);
}