#ifndef FILE_H
#define FILE_H

namespace File
{
    std::string ReadFile(const std::string path);
    bool WriteFile(const std::string path, const std::string& contents);
}
#endif
