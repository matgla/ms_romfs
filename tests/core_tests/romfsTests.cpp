#include "romfs.hpp"
#include "gtest/gtest.h"

#include "fileHelper.hpp"
#include "fileSystemHeader.hpp"
#include "utils.hpp"

#include <vector>

class romfs_fixture : public ::testing::Test {

  protected:
    std::vector<u8> memory;
    std::unique_ptr<RomFsDisk> disk;

    virtual void SetUp() {
        memory = readFileToMemory("test_img.romfs");
        disk.reset(new RomFsDisk(memory.data()));
    };
};

// TEST_F(romfs_fixture, shouldOpenFileInRoot) {
//     auto file = disk->openFile("/.gitignore");
//     EXPECT_EQ(true, file.open);

//     std::string name = file.fileHdr.get_name();
//     EXPECT_EQ(".gitignore", name);
// }

// TEST_F(romfs_fixture, shouldOpenFileInDirectory) {
//     auto file = disk->openFile("/inc/romfs.h");
//     EXPECT_EQ(true, file.open);

//     std::string name = file.fileHdr.get_name();
//     EXPECT_EQ("romfs.h", name);
// }

// TEST_F(romfs_fixture, shouldNotOpenDirectoryInRoot) {
//     auto file = disk->openFile("/inc");
//     EXPECT_EQ(false, file.open);
// }

// TEST_F(romfs_fixture, shouldNotOpenDirectoryInDir) {
//     auto file = disk->openFile("/CMakeFiles/msos_romfs.dir");
//     EXPECT_EQ(false, file.open);
// }

// TEST_F(romfs_fixture, shouldNotOpenNotExistingFile) {
//     auto file = disk->openFile("/notexist.txt12");
//     EXPECT_EQ(false, file.open);
// }

TEST_F(romfs_fixture, shouldReturnFileListInRoot) {
    // auto files = disk->getAllFileNamesInDir("/");
    // EXPECT_EQ(".", files[0]);
    // EXPECT_EQ("..", files[1]);
    // EXPECT_EQ("CMakeCache.txt", files[2]);
    // EXPECT_EQ("inc", files[3]);
    // EXPECT_EQ(".git", files[4]);
    // EXPECT_EQ(".gitignore", files[5]);
}

TEST_F(romfs_fixture, filesSizeShouldBe0ForNonExistingDir) {
    // auto files = disk->getAllFileNamesInDir("/notexist");
    // EXPECT_EQ(0, files.size());
}