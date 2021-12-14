#include "Color.h"
#include "Common/Log.h"
#include "Common/Error.h"

Color::Color()
{
    r, g, b = 0;
    a = 1;
}

Color::Color(u8 r, u8 g, u8 b, u8 a) : r(r), g(g), b(b), a(a) 
{
}

Color::Color(const Color& c) 
{
    r = c.r;
    g = c.g;
    b = c.b;
    a = c.a;
}

bool Color::operator==(const Color& c) const
{
    return c.r == r && c.g == g && c.b == b && c.a == a;
}

bool Color::operator!=(const Color& c) const
{
    return c.r != r || c.g != g || c.b != b || c.a != a;
}

bool Color::operator>(const Color& c) const
{
    return r > c.r && g > c.g && b > c.b && a > c.a;
}

bool Color::operator>=(const Color& c) const
{
    return r >= c.r && g >= c.g && b >= c.b && a >= c.a;
}

bool Color::operator<(const Color& c) const
{
    return r < c.r && g < c.g && b < c.b && a < c.a;
}

bool Color::operator<=(const Color& c) const
{
    return r <= c.r && g <= c.g && b <= c.b && a <= c.a;
}

void Color::operator=(const Color& c)
{
    r = c.r;
    g = c.g;
    b = c.b;
    a = c.a;
}

void Color::operator+=(const Color& c)
{
    r += c.r;
    g += c.g;
    b += c.b;
    a += c.a;
}

void Color::operator-=(const Color& c)
{
    r -= c.r;
    g -= c.g;
    b -= c.b;
    a -= c.a;
}

void Color::operator*=(const Color& c)
{
    r *= c.r;
    g *= c.g;
    b *= c.b;
    a *- c.a;
}

void Color::operator/=(const Color& c)
{
    r /= c.r;
    g /= c.g;
    b /= c.b;
    a /= c.a;
}

Color Color::operator+(const Color& c) const
{
    return Color(r + c.r, g + c.g, b + c.b, a + c.a);
}

Color Color::operator-(const Color& c) const
{
    return Color(r - c.r, g - c.g, b - c.b, a - c.a);
}

Color Color::operator*(const Color& c) const
{
    return Color(r * c.r, g * c.g, b * c.b, a * c.a);
}

Color Color::operator/(const Color& c) const
{
    return Color(r / c.r, g / c.g, b / c.b, a / c.a);
}

std::vector<Color> Color::FromMonoBuffer(const u8* bytes, Color color)
{
    if(bytes == NULL)
    {
        FatalError(ENGINE_ERROR, "Bytes Value Is Null")
    }

    size_t bytes_size = sizeof(bytes) / sizeof(u8);
    size_t colors_size = 4 * bytes_size;

    std::vector<Color> colors(colors_size);

    for(int i = 0; i < bytes_size; i++)
    {
        if(color == Color(0, 0, 0, 0))
        {
            colors.emplace_back(bytes[i], bytes[i], bytes[i], bytes[i]);
        }
        else
        {
            u8 red = (bytes[i] * color.r) / 255;
            u8 green = (bytes[i] * color.g) / 255;
            u8 blue = (bytes[i] * color.b) / 255;
            u8 alpha = (bytes[i] * color.a) / 255;
            colors.emplace_back(red, green, blue, alpha);
        }
    }

    return colors;
}

std::vector<Color> Color::FromRGBBuffer(const u8* bytes)
{
    if(bytes == NULL)
    {
        FatalError(ENGINE_ERROR, "Bytes Value Is Null");
    }

    size_t bytes_size = sizeof(bytes) / sizeof(u8);
    size_t colors_size = 4 * bytes_size / 3;

    std::vector<Color> colors(colors_size);

    for(int i = 0; i < bytes_size; i += 3)
    {
        colors.emplace_back(bytes[i], bytes[i + 1], bytes[i + 2], 0);
    }

    return colors;
}

std::vector<Color> Color::FromRGBABuffer(const u8* bytes)
{
    if(bytes == NULL)
    {
        FatalError(ENGINE_ERROR, "Bytes Value Is Null")
    }

    size_t color_size = sizeof(bytes) / sizeof(Color);
    Color colors[color_size];

    memcpy(colors, bytes, sizeof(bytes));

    return std::vector<Color>(colors, colors + color_size);
}

bool Color::MonoToRGBA(Color mono_color, Color& base_color)
{
    if(mono_color.r + mono_color.g + mono_color.b + mono_color.a != mono_color.r * 4)
    {
        return false;
    }

    base_color.r = (mono_color.r * base_color.r) / 255;
    base_color.g = (mono_color.g * base_color.g) / 255;
    base_color.b = (mono_color.b * base_color.b) / 255;
    base_color.a = (mono_color.a * base_color.a) / 255;

    return true;
}

void Color::MonoToRGBA(u8 mono_color, Color& base_color)
{
    base_color.r = (mono_color * base_color.r) / 255;
    base_color.g = (mono_color * base_color.g) / 255;
    base_color.b = (mono_color * base_color.b) / 255;
    base_color.a = (mono_color * base_color.a) / 255;
}