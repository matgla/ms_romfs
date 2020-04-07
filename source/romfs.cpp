#include "romfs/romfs.hpp"

#include "romfs/directory.hpp"

namespace romfs
{

RomFsDisk::RomFsDisk(const uint8_t* memory)
    : memory_start_(memory)
    , file_system_header_(memory)
{
    valid_ = file_system_header_.init();
}

FileHeader RomFsDisk::get_first_file_header() const
{
    const uint8_t* first_file_header = make_aligned_ptr(memory_start_ + file_system_header_.get_header_size(), 16);
    FileHeader f(first_file_header);
    return f;
}

std::optional<Directory> RomFsDisk::get_directory(const std::string_view& path) const
{
    if (!valid_)
    {
        return std::optional<Directory>{};
    }

    if (path.front() != '/')
    {
        return {};
    }

    const std::size_t offset_to_first_file = file_system_header_.get_header_size();

    Directory dir(memory_start_, offset_to_first_file);

    std::string_view tmp_path = path;

    while(tmp_path.size())
    {
        tmp_path.remove_prefix(std::min(tmp_path.find_first_not_of("/"), tmp_path.size()));

        if (!tmp_path.size())
        {
            return dir;
        }

        std::size_t slash_pos = tmp_path.find("/");

        if (slash_pos == std::string_view::npos)
        {
            slash_pos = 0;
            return dir.get_directory(tmp_path);
        }

        std::string_view file = tmp_path.substr(0, slash_pos);
        tmp_path = tmp_path.substr(slash_pos + 1, tmp_path.size() - slash_pos);
        auto maybe_dir = dir.get_directory(file);
        if (!maybe_dir)
        {
            return {};
        }

        dir = *maybe_dir;
    }

    return dir;
}

} // namespace romfs
