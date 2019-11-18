#include "romfs.hpp"
#include <iostream>

RomFsDisk::RomFsDisk(const uint8_t* memory)
    : memory_start_(memory)
    , file_system_header_(memory)
{
}

FileHeader RomFsDisk::get_first_file_header() const
{
    const uint8_t* first_file_header = make_aligned_ptr(memory_start_ + file_system_header_.get_header_size(), 16);
    FileHeader{first_file_header};
}

// File RomFsDisk::openFile(const std::string_view& filePath) {
//     auto directoryStart = firstFileHeader;

//     auto files = getFilesArray(std::string(filePath));
//     for (int i = 0; i < files.size(); i++) {
//         auto fileHeader = findFileHeaderIntoDir(directoryStart, files[i]);
//         if (!fileHeader.exists()) {
//             return {};
//         }
//         if (fileHeader.get_file_type() != FileType::DIRECTORY &&
//             i != files.size() - 1) {
//             return {};
//         }
//         if (i != files.size() - 1)
//             directoryStart = memory_start_ + fileHeader.get_specinfo();
//         else {
//             if (fileHeader.get_file_type() != FileType::REGULAR_FILE) {
//                 return {};
//             }
//             directoryStart = fileHeader.get_start_ptr();
//         }
//     }
//     FileHeader fHdr(directoryStart);

//     File file;
//     return file;
// }

std::vector<std::string>
RomFsDisk::getAllFileNamesInDir(const std::string& directoryPath) {
    auto directoryStart = get_first_file_header();
    std::cerr << directoryStart.get_size() << std::endl;
    return {};
}

FileHeader RomFsDisk::findFileHeaderIntoDir(u8 *directoryStart,
                                            const std::string &fileName) {
    // auto filePtr = directoryStart == nullptr ? firstFileHeader : directoryStart;
    // while (filePtr != nullptr) {
    //     FileHeader fHdr(filePtr);
    //     if (fileName == fHdr.get_name()) {
    //         return fHdr;
    //     }
    //     auto offset = fHdr.get_next_file_offset();
    //     if (0 == offset) {
    //         filePtr = nullptr;
    //     } else {
    //         filePtr = memory_start_ + offset;
    //     }
    // }
    return FileHeader(nullptr);
}
