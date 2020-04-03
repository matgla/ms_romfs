#pragma once

#include <cstdint>
#include <string_view>
#include <optional>

#include "fileHeader.hpp"
#include "fileSystemHeader.hpp"
#include "directory.hpp"
#include "utils.hpp"

namespace romfs
{

class RomFsDisk
{
public:
    RomFsDisk(const uint8_t* memory);

    std::optional<Directory> get_directory(const std::string_view& path) const;

private:
    FileHeader get_first_file_header() const;

    bool valid_;
    const uint8_t* memory_start_;
    FileSystemHeader file_system_header_;
};

} // namespace romfs

