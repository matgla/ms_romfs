#include "directory.hpp"

#include <iostream>

Directory::Directory(const uint8_t* address, const std::size_t offset)
    : address_(address)
    , offset_(offset)
{
    std::cerr << "Directory at address: 0x" << std::hex << offset_ << std::endl;
}

Directory::Directory(const Directory& directory)
    : address_(directory.address_)
    , offset_(directory.offset_)
{

}

Directory& Directory::operator=(const Directory& directory)
{
    address_ = directory.address_;
    offset_ = directory.offset_;
    return *this;
}

std::optional<Directory> Directory::get_directory(const std::string_view& name) const
{
    for (auto file : *this)
    {
         if (file.get_name() == name)
        {
            if (file.get_file_type() == FileType::DIRECTORY)
            {
                return Directory(address_, file.get_specinfo());
            }
            else if (file.get_file_type() == FileType::HARD_LINK)
            {
                FileHeader directory_start(address_ + file.get_specinfo());
                std::cerr << "link: " << directory_start.get_name() << ", next: 0x" << directory_start.get_next_file_offset() << ", specinfo: " << directory_start.get_specinfo() << std::endl;
                return Directory(address_, directory_start.get_specinfo());
            }
        }
    }

    return {};
}


DirectoryIterator Directory::begin() const
{
    return DirectoryIterator(address_, offset_);
}

DirectoryIterator Directory::end() const
{
    return DirectoryIterator(address_, 0);
}

