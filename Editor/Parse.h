#ifndef PARSE_H
#define PARSE_H

#include <Actor.h>
#include <Level.h>

namespace Parse
{
    Level OpenLevelFile(std::string file_path);

    template<typename T>
    size_t FindNumber(std::string x, size_t pos);
}

#endif