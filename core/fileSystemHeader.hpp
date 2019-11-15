#pragma once

#include <memory>
#include <string_view>
#include <cstring>

#include "utils.hpp"
#include "reader.hpp"

class FileSystemHeader final
{
public:
    FileSystemHeader(uint8_t* memory);

    void setMemoryStart(uint8_t* memory);

    uint32_t getSize();
    uint32_t getChecksum();
    const char* getVolumeName();
    const uint8_t* getHeaderEnd();

  private:
    uint32_t fs_size_;
    uint32_t fs_checksum_;

    bool validate_start_cookie();
    std::string_view volume_name_;

    Reader reader_;
    const uint8_t* memory_start_;
    uint8_t* header_end_;
};