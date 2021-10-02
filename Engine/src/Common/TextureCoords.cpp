#include "TextureCoords.h"

TextureCoords::TextureCoords()
{
    u, v = 0;
}

TextureCoords::TextureCoords(float u, float v) : u(u), v(v)
{
}

TextureCoords::TextureCoords(const TextureCoords& t) 
{
    u = t.u;
    v = t.v;
}

bool TextureCoords::operator==(const TextureCoords& t) const
{
    return u == t.u && v == t.v;
}

bool TextureCoords::operator!=(const TextureCoords& t) const
{
    return u != t.u || v != t.v;
}

bool TextureCoords::operator>(const TextureCoords& t) const
{
    return u > t.u && v > t.v;
}

bool TextureCoords::operator>=(const TextureCoords& t) const
{
    return u >= t.u && v >= t.v;
}

bool TextureCoords::operator<(const TextureCoords& t) const
{
    return u < t.u && v < t.v;
}

bool TextureCoords::operator<=(const TextureCoords& t) const
{
    return u <= t.u && v <= t.v;
}

void TextureCoords::operator=(const TextureCoords& t)
{
    u = t.u;
    v = t.v;
}

void TextureCoords::operator+=(const TextureCoords& t)
{
    u += t.u;
    v += t.v;
}

void TextureCoords::operator-=(const TextureCoords& t)
{
    u -= t.u;
    v -= t.v;
}

void TextureCoords::operator*=(const TextureCoords& t)
{
    u *= t.u;
    v *= t.v;
}

void TextureCoords::operator/=(const TextureCoords& t)
{
    u /= t.u;
    v /= t.v;
}

TextureCoords TextureCoords::operator+(const TextureCoords& t) const
{
    return TextureCoords(u + t.u, v + t.v);
}

TextureCoords TextureCoords::operator-(const TextureCoords& t) const
{
    return TextureCoords(u - t.u, v - t.v);
}

TextureCoords TextureCoords::operator*(const TextureCoords& t) const
{
    return TextureCoords(u * t.u, v * t.v);
}

TextureCoords TextureCoords::operator/(const TextureCoords& t) const
{
    return TextureCoords(u / t.u, v / t.v);
}

std::vector<TextureCoords> TextureCoords::ToVectorArray(const float* coords)
{
    size_t tc_size = sizeof(coords) / sizeof(TextureCoords);
    TextureCoords tc[tc_size];

    memcpy(tc, coords, sizeof(coords));

    return std::vector<TextureCoords>(tc, tc + tc_size);
}