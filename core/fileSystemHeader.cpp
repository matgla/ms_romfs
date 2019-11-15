#include "fileSystemHeader.hpp"

#include <cassert>
#include <cstring>

FileSystemHeader::FileSystemHeader(uint8_t* memory)
    : fs_size_(0)
    , fs_checksum_(0)
    , volume_name_("")
    , reader_(makeAlignedPtr(memory, 16))
{
    assert(validate_start_cookie());

    fs_size_ = reader_.read<uint32_t>();
    fs_checksum_ = reader_.read<uint32_t>();
    volume_name_ = reader_.read_string_with_padding(16);
}

bool FileSystemHeader::validate_start_cookie()
{
    const std::string_view cookie = reader_.read_string(8);
    return cookie == "-rom1fs-";
}

uint32_t FileSystemHeader::getSize()
{
    return fs_size_;
}

uint32_t FileSystemHeader::getChecksum()
{
    return fs_checksum_;
}

const char* FileSystemHeader::getVolumeName()
{
    return volume_name_.data();
}

const uint8_t* FileSystemHeader::getHeaderEnd() {
    return reader_.address();
}
