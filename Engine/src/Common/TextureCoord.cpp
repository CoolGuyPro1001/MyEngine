#include "TextureCoord.h"

TextureCoord::TextureCoord()
{
    u, v = 0;
}

TextureCoord::TextureCoord(float u, float v) : u(u), v(v)
{
}

TextureCoord::TextureCoord(const TextureCoord& t)
{
    u = t.u;
    v = t.v;
}

bool TextureCoord::operator==(const TextureCoord& t) const
{
    return u == t.u && v == t.v;
}

bool TextureCoord::operator!=(const TextureCoord& t) const
{
    return u != t.u || v != t.v;
}

bool TextureCoord::operator>(const TextureCoord& t) const
{
    return u > t.u && v > t.v;
}

bool TextureCoord::operator>=(const TextureCoord& t) const
{
    return u >= t.u && v >= t.v;
}

bool TextureCoord::operator<(const TextureCoord& t) const
{
    return u < t.u && v < t.v;
}

bool TextureCoord::operator<=(const TextureCoord& t) const
{
    return u <= t.u && v <= t.v;
}

void TextureCoord::operator=(const TextureCoord& t)
{
    u = t.u;
    v = t.v;
}

void TextureCoord::operator+=(const TextureCoord& t)
{
    u += t.u;
    v += t.v;
}

void TextureCoord::operator-=(const TextureCoord& t)
{
    u -= t.u;
    v -= t.v;
}

void TextureCoord::operator*=(const TextureCoord& t)
{
    u *= t.u;
    v *= t.v;
}

void TextureCoord::operator/=(const TextureCoord& t)
{
    u /= t.u;
    v /= t.v;
}

TextureCoord TextureCoord::operator+(const TextureCoord& t) const
{
    return TextureCoord(u + t.u, v + t.v);
}

TextureCoord TextureCoord::operator-(const TextureCoord& t) const
{
    return TextureCoord(u - t.u, v - t.v);
}

TextureCoord TextureCoord::operator*(const TextureCoord& t) const
{
    return TextureCoord(u * t.u, v * t.v);
}

TextureCoord TextureCoord::operator/(const TextureCoord& t) const
{
    return TextureCoord(u / t.u, v / t.v);
}

std::vector<TextureCoord> TextureCoord::ToVectorArray(const float* coords)
{
    size_t tc_size = sizeof(coords) / sizeof(TextureCoord);
    TextureCoord tc[tc_size];

    memcpy(tc, coords, sizeof(coords));

    return std::vector<TextureCoord>(tc, tc + tc_size);
}
