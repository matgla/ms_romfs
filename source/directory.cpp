#include "romfs/directory.hpp"

namespace romfs
{

Directory::Directory(const uint8_t* address, const std::size_t offset)
    : address_(address)
    , offset_(offset)
{
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

std::optional<Directory> Directory::get_directory(const std::string_view name) const
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
                return Directory(address_, directory_start.get_specinfo());
            }
        }
    }

    return {};
}

std::optional<FileHeader> Directory::get_file_header() const
{
    auto file = get_file(".");

    if (!file)
    {
        return {};
    }

    if (file->get_file_type() == FileType::HARD_LINK)
    {
        return FileHeader(address_ + file->get_specinfo());
    }

    return file;
}


std::optional<FileHeader> Directory::get_file(const std::string_view name) const
{
    for (auto file : *this)
    {
        if (file.get_name() == name)
        {
            if (file.get_file_type() == FileType::REGULAR_FILE)
            {
                return file;
            }
            if (file.get_file_type() == FileType::DIRECTORY)
            {
                return file;
            }
            if (file.get_file_type() == FileType::HARD_LINK)
            {
                return file;
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

} // namespace romfs
