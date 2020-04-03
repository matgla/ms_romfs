#include "romfs/fileSystemHeader.hpp"

#include <cassert>
#include <cstring>

namespace romfs
{

FileSystemHeader::FileSystemHeader(const uint8_t* memory)
    : fs_size_(0)
    , fs_checksum_(0)
    , volume_name_("")
    , reader_(make_aligned_ptr<uint8_t>(memory, 16))
{
    // assert(validate_start_cookie());
}

bool FileSystemHeader::init()
{
    if (!validate_start_cookie())
    {
        return false;
    }
    fs_size_ = reader_.read<uint32_t>();
    fs_checksum_ = reader_.read<uint32_t>();
    volume_name_ = reader_.read_string_with_padding(16);
    return true;
}

bool FileSystemHeader::validate_start_cookie()
{
    const std::string_view cookie = reader_.read_string(8);
    return cookie == "-rom1fs-";
}

uint32_t FileSystemHeader::get_volume_size() const
{
    return fs_size_;
}

uint32_t FileSystemHeader::get_checksum() const
{
    return fs_checksum_;
}

std::string_view FileSystemHeader::get_volume_name() const
{
    return volume_name_;
}

std::size_t FileSystemHeader::get_header_size() const
{
    return reader_.get_readed_bytes();
}

} // namespace romfs
