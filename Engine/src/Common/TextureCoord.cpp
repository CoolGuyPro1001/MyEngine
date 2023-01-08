#include "TextureCoord.h"

#include "Common/Error.h"

TextureCoord::TextureCoord()
{
    u, v, w = 0;
}

TextureCoord::TextureCoord(float u, float v, float w) : u(u), v(v), w(w)
{
}

TextureCoord::TextureCoord(const TextureCoord& t)
{
    u = t.u;
    v = t.v;
    w = t.w;
}

bool TextureCoord::operator==(const TextureCoord& t) const
{
    return u == t.u && v == t.v && w == t.w;
}

bool TextureCoord::operator!=(const TextureCoord& t) const
{
    return u != t.u || v != t.v || w != t.w;
}

bool TextureCoord::operator>(const TextureCoord& t) const
{
    return u > t.u && v > t.v && w > t.w;
}

bool TextureCoord::operator>=(const TextureCoord& t) const
{
    return u >= t.u && v >= t.v && w >= t.w;
}

bool TextureCoord::operator<(const TextureCoord& t) const
{
    return u < t.u && v < t.v && w < t.w;
}

bool TextureCoord::operator<=(const TextureCoord& t) const
{
    return u <= t.u && v <= t.v && w <= t.w;
}

void TextureCoord::operator=(const TextureCoord& t)
{
    u = t.u;
    v = t.v;
    w = t.w;
}

void TextureCoord::operator+=(const TextureCoord& t)
{
    u += t.u;
    v += t.v;
    w += t.w;
}

void TextureCoord::operator-=(const TextureCoord& t)
{
    u -= t.u;
    v -= t.v;
    w -= t.w;
}

void TextureCoord::operator*=(const TextureCoord& t)
{
    u *= t.u;
    v *= t.v;
    w *= t.w;
}

void TextureCoord::operator/=(const TextureCoord& t)
{
    auto divide_by_zero_error = [=](char c)
    {
        CriticalErrorArgs(ENGINE_ERROR, "Can't Divide Texture Coordinate %c By 0. Setting %c To 0\n", c);
        return 1;
    };

    u /= (u != 0) ? t.u : divide_by_zero_error('U');
    v /= (v != 0) ? t.v : divide_by_zero_error('V');
    w /= (w != 0) ? t.w : divide_by_zero_error('W');
}

TextureCoord TextureCoord::operator+(const TextureCoord& t) const
{
    return TextureCoord(u + t.u, v + t.v, w + t.w);
}

TextureCoord TextureCoord::operator-(const TextureCoord& t) const
{
    return TextureCoord(u - t.u, v - t.v, w - t.w);
}

TextureCoord TextureCoord::operator*(const TextureCoord& t) const
{
    return TextureCoord(u * t.u, v * t.v, w * t.w);
}

TextureCoord TextureCoord::operator/(const TextureCoord& t) const
{
    float temp_u = u;
    float temp_v = v;
    float temp_w = w;

    auto divide_by_zero_error = [=](char c)
    {
        CriticalErrorArgs(ENGINE_ERROR, "Can't Divide Texture Coordinate %c By 0. Returning Original Value\n", c);
        return 1;
    };

    temp_u /= (t.u != 0) ? t.u : divide_by_zero_error('U');
    temp_v /= (t.v != 0) ? t.v : divide_by_zero_error('V');
    temp_w /= (t.w != 0) ? t.w : divide_by_zero_error('W');

    return TextureCoord(temp_u, temp_v, temp_w);
}

std::vector<TextureCoord> TextureCoord::ToVectorArray(const float* coords)
{
    size_t tc_size = sizeof(coords) / sizeof(TextureCoord);
    TextureCoord tc[tc_size];

    memcpy(tc, coords, sizeof(coords));

    return std::vector<TextureCoord>(tc, tc + tc_size);
}
