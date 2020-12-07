#include "File.h"

std::string File::ReadFile(const std::string path)
{
    std::ifstream file(path);
    std::string line;
    std::string contents;

    if(file.is_open())
    {
        while(std::getline(file, line))
        {
            contents += line;
            contents += "\n";
        }
        
        file.close();
        return contents;
    }

    return "";
}

bool File::WriteFile(const std::string path, const std::string& contents)
{
    std::ofstream file(path);
    if(file.is_open())
    {
        file << contents;
        file.close();
        return true;
    }

    return false;
}