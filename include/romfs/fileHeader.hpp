#pragma once

#include <string_view>

#include "romfs/utils.hpp"
#include "romfs/reader.hpp"

namespace romfs
{

enum class FileType : uint8_t
{
    HARD_LINK = 0,
    DIRECTORY = 1,
    REGULAR_FILE = 2,
    SYMBOLIC_LINK = 3,
    BLOCK_DEVICE = 4,
    CHAR_DEVICE = 5,
    SOCKET = 6,
    FIFO = 7,
    NOT_EXIST
};

std::string_view to_string(const FileType fileType);

class FileHeader final
{
  public:
    FileHeader(const uint8_t* memory);

    uint32_t get_next_file_offset() const;
    uint32_t get_specinfo() const;
    uint32_t get_size() const;
    uint32_t get_checksum() const;
    std::string_view get_name() const;

    FileType get_file_type() const;
    bool exists() const;
    const uint8_t* data() const;

private:
    void read_next_file_offset();

    const uint8_t* memory_start_;
    const uint8_t* data_start_;
    Reader reader_;

    uint32_t next_file_header_;
    uint32_t spec_info_;
    uint32_t file_size_;
    uint32_t checksum_;
    std::string_view name_;

    FileType filetype_;
};

} // namespace romfs
