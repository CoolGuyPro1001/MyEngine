#include "Directory.h"

namespace Directory
{
    DirectoryStatus NewFolder(std::filesystem::path path)
    {
        if(std::filesystem::exists(path))
        {
            return DirectoryStatus::EXISTS;
        }

        std::filesystem::path p = path;
        std::filesystem::create_directory(p);
        return DirectoryStatus::SUCCESS;
    }

    DirectoryStatus DeleteFolder(std::filesystem::path path, bool ignore_files)
    {
        std::error_code error;
        
        if(!std::filesystem::exists(path))
        {
            return DirectoryStatus::REMOVED;
        }

        if(!ignore_files && !path.empty())
        {
            return DirectoryStatus::NOT_EMPTY;
        }

        unsigned int files_removed = std::filesystem::remove_all(path, error);
        return DirectoryStatus::SUCCESS;
    }
}