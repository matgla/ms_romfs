#include "directoryIterator.hpp"

DirectoryIterator::DirectoryIterator(const uint8_t* address, std::size_t offset)
    : address_(address)
    , offset_(offset)

{
    FileHeader header(address + offset);
}

const DirectoryIterator& DirectoryIterator::operator++()
{
    FileHeader header(address_ + offset_);
    offset_ = header.get_next_file_offset();
    return *this;
}

bool DirectoryIterator::operator!=(const DirectoryIterator& it) const
{
    return offset_ != it.offset_;
}

const FileHeader DirectoryIterator::operator*() const
{
    FileHeader header(address_ + offset_);
    return header;
}