#ifndef TEXTURECOORDS_H
#define TEXTURECOORDS_H

struct TextureCoords
{
    float u, v;

    TextureCoords(float u, float v);
    TextureCoords();
    TextureCoords(const TextureCoords& t);

    bool operator==(const TextureCoords& t) const;
    bool operator!=(const TextureCoords& t) const;
    bool operator>(const TextureCoords& t) const;
    bool operator>=(const TextureCoords& t) const;
    bool operator<(const TextureCoords& t) const;
    bool operator<=(const TextureCoords& t) const;
    void operator=(const TextureCoords& t);
    void operator+=(const TextureCoords& t);
    void operator-=(const TextureCoords& t);
    void operator*=(const TextureCoords& t);
    void operator/=(const TextureCoords& t);
    TextureCoords operator+(const TextureCoords& t) const;
    TextureCoords operator-(const TextureCoords& t) const;
    TextureCoords operator*(const TextureCoords& t) const;
    TextureCoords operator/(const TextureCoords& t) const;

    static std::vector<TextureCoords> ToVectorArray(const float* coords);
};
#endif