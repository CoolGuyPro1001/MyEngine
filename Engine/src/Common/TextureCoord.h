#ifndef TEXTURECOORD_H
#define TEXTURECOORD_H

struct TextureCoord
{
    float u, v;

    TextureCoord(float u, float v);
    TextureCoord();
    TextureCoord(const TextureCoord& t);

    bool operator==(const TextureCoord& t) const;
    bool operator!=(const TextureCoord& t) const;
    bool operator>(const TextureCoord& t) const;
    bool operator>=(const TextureCoord& t) const;
    bool operator<(const TextureCoord& t) const;
    bool operator<=(const TextureCoord& t) const;
    void operator=(const TextureCoord& t);
    void operator+=(const TextureCoord& t);
    void operator-=(const TextureCoord& t);
    void operator*=(const TextureCoord& t);
    void operator/=(const TextureCoord& t);
    TextureCoord operator+(const TextureCoord& t) const;
    TextureCoord operator-(const TextureCoord& t) const;
    TextureCoord operator*(const TextureCoord& t) const;
    TextureCoord operator/(const TextureCoord& t) const;

    static std::vector<TextureCoord> ToVectorArray(const float* coords);
};
#endif
