#include "romfs.hpp"
#include <iostream>

#include "directory.hpp"

RomFsDisk::RomFsDisk(const uint8_t* memory)
    : memory_start_(memory)
    , file_system_header_(memory)
{
}

FileHeader RomFsDisk::get_first_file_header() const
{
    const uint8_t* first_file_header = make_aligned_ptr(memory_start_ + file_system_header_.get_header_size(), 16);
    std::cerr << "test: " << std::hex << (int)(first_file_header[0]) << " " << (int)(first_file_header[1]) << std::endl;
    FileHeader f(first_file_header);
    return f;
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

// std::vector<std::string>
// RomFsDisk::getAllFileNamesInDir(const std::string& directoryPath) {
//

//     Directory dir(memory_start_, offset_to_first_file);

//     std::cerr << "Files under: /" << std::endl;
//     for (auto file : dir)
//     {
//         std::cerr << file.get_name() << std::endl;
//     }

//     return {};
// }

std::optional<Directory> RomFsDisk::get_directory(const std::string_view& path) const
{
    // trim //
    // open folder till /
    // trim //
    // open folder
    if (path.front() != '/')
    {
        return {};
    }

    const uint32_t offset_to_first_file = file_system_header_.get_header_size();

    Directory dir(memory_start_, offset_to_first_file);

    std::string_view tmp_path = path;

    while(tmp_path.size())
    {
        tmp_path.remove_prefix(std::min(tmp_path.find_first_not_of("/"), tmp_path.size()));

        if (!tmp_path.size())
        {
            return dir;
        }

        std::size_t slash_pos = tmp_path.find("/");

        if (slash_pos == std::string_view::npos)
        {
            slash_pos = 0;
            return dir.get_directory(tmp_path);
        }

        std::string_view file = tmp_path.substr(0, slash_pos);
        tmp_path = tmp_path.substr(slash_pos + 1, tmp_path.size() - slash_pos);
        auto maybe_dir = dir.get_directory(file);
        if (!maybe_dir)
        {
            return {};
        }

        dir = *maybe_dir;
    }

    return dir;
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
