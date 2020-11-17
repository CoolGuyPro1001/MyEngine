#ifndef PARSE_H
#define PARSE_H

#include <Common/Units.h>
#include <File.h>
#include <Actor.h>
#include <Common/Hex.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace Parse
{
    Shared<Model> FileToModel(std::string file_path);

    template<typename T>
    size_t FindNumber(std::string x, size_t pos);
    float Normalize(int num, int low, int high);
}

#endif