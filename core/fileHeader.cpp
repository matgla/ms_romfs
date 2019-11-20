#include "fileHeader.hpp"

#include <iostream>

std::string_view to_string(const FileType filetype)
{
    switch (filetype)
    {
        case FileType::BLOCK_DEVICE: return "b";
        case FileType::CHAR_DEVICE: return "c";
        case FileType::DIRECTORY: return "d";
        case FileType::FIFO: return "fi";
        case FileType::HARD_LINK: return "h";
        case FileType::REGULAR_FILE: return "f";
        case FileType::SOCKET: return "s";
        case FileType::SYMBOLIC_LINK: return "l";
    }
    return "u";
}

FileHeader::FileHeader(const uint8_t* memory)
    : memory_start_(memory)
    , reader_(memory)
    , next_file_header_(0)
    , spec_info_(0)
    , file_size_(0)
    , data_start_(nullptr)
    , filetype_(FileType::NOT_EXIST)
{
    read_next_file_offset();
    spec_info_ = reader_.read<uint32_t>();
    file_size_ = reader_.read<uint32_t>();
    checksum_ = reader_.read<uint32_t>();
    name_ = reader_.read_string_with_padding(16);

    data_start_ = memory_start_ + reader_.get_readed_bytes();
}

uint32_t FileHeader::get_next_file_offset() const
{
    return next_file_header_;
}

uint32_t FileHeader::get_specinfo() const
{
    return spec_info_;
}

uint32_t FileHeader::get_size() const
{
    return file_size_;
}

uint32_t FileHeader::get_checksum() const
{
    return checksum_;
}

std::string_view FileHeader::get_name() const
{
    return name_;
}

void FileHeader::read_next_file_offset()
{
    uint32_t next_file = reader_.read<uint32_t>();
    constexpr uint32_t next_file_header_mask = 0xfffffff0;
    constexpr uint32_t file_info_mask = 0x00000007;
    next_file_header_ = next_file & next_file_header_mask;
    uint8_t file_info = next_file & file_info_mask;
    filetype_ = static_cast<FileType>(file_info);
}

FileType FileHeader::get_file_type() const
{
    return filetype_;
}

bool FileHeader::exists() const
{
    return filetype_ != FileType::NOT_EXIST;
}

u8 *FileHeader::get_start_ptr() {
    return const_cast<uint8_t*>(memory_start_);
}

uint8_t* FileHeader::get_data_ptr() {
    return const_cast<uint8_t*>(data_start_);
}