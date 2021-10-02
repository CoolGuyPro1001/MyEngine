#ifndef COLOR_H
#define COLOR_H

struct Color
{
    u8 r, g, b, a;

    Color();
    Color(u8 r, u8 g, u8 b, u8 a);
    Color(const Color& c);

    bool operator==(const Color& c) const;
    bool operator!=(const Color& c) const;
    bool operator>(const Color& c) const;
    bool operator>=(const Color& c) const;
    bool operator<(const Color& c) const;
    bool operator<=(const Color& c) const;
    void operator=(const Color& c);
    void operator+=(const Color& c);
    void operator-=(const Color& c);
    void operator*=(const Color& c);
    void operator/=(const Color& c);
    Color operator+(const Color& c) const;
    Color operator-(const Color& c) const;
    Color operator*(const Color& c) const;
    Color operator/(const Color& c) const;

    static std::vector<Color> FromMonoBuffer(const u8* bytes, Color color = Color(0, 0, 0, 0));
    static std::vector<Color> FromRGBBuffer(const u8* bytes);
    static std::vector<Color> FromRGBABuffer(const u8* bytes);

    static bool MonoToRGBA(Color mono_color, Color& base_color);
    static void MonoToRGBA(u8 mono_color, Color& base_color);
};
#endif