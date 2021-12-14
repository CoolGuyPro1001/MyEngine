#ifndef BINARY_H
#define BINARY_H

class Hex;
struct Binary
{
    std::string val;
    Binary(std::string val);
    Binary();

    size_t Size();
    size_t ToDecimal();
    Hex ToHex();
};
#endif
