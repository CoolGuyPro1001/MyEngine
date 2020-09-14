#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <filesystem>

namespace Directory
{
    enum class DirectoryStatus
    {
        SUCCESS,
        EXISTS,
        REMOVED,
        NOT_EMPTY
    };

    DirectoryStatus NewFolder(std::filesystem::path path);
    DirectoryStatus DeleteFolder(std::filesystem::path path, bool ignore_files);
}
#endif