#pragma once

#include <cstdint>
#include <string_view>
#include <optional>

#include "romfs/directoryIterator.hpp"
#include "romfs/file.hpp"

namespace romfs
{

class Directory
{
public:
    Directory(const uint8_t* address, const std::size_t offset);
    Directory(const Directory& directory);
    Directory& operator=(const Directory& directory);

    std::optional<Directory> get_directory(const std::string_view& name) const;

    DirectoryIterator begin() const;
    DirectoryIterator end() const;

    std::optional<File> get_file(const std::string_view& name) const;
private:
    const uint8_t* address_;
    std::size_t offset_;
};

} // namespace romfs


