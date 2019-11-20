#pragma once

#include <memory>
#include <string_view>
#include <cstring>

#include "utils.hpp"
#include "reader.hpp"

class FileSystemHeader final
{
public:
    FileSystemHeader(const uint8_t* memory);

    uint32_t get_checksum() const;
    std::string_view get_volume_name() const;
    std::size_t get_header_size() const;
    uint32_t get_volume_size() const;

private:
    uint32_t fs_size_;
    uint32_t fs_checksum_;

    bool validate_start_cookie();
    std::string_view volume_name_;

    Reader reader_;
    const uint8_t* memory_start_;
};