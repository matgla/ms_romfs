#include "romfs.hpp"
#include "gtest/gtest.h"

#include "fileHelper.hpp"
#include "fileSystemHeader.hpp"
#include "utils.hpp"

#include <vector>

class romfs_fixture : public ::testing::Test {

  protected:
    std::vector<u8> disk;

    virtual void SetUp() {
        disk = readFileToMemory("test_img.romfs");
    };
};

TEST_F(romfs_fixture, readFileSystemInfo) {
}
