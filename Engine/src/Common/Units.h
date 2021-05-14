#ifndef UNITS_H
#define UNITS_H

struct Vector2;
struct Vector3;

struct Vector2
{
    float x, y;

    Vector2();
    Vector2(float x, float y);
    Vector2(const Vector2& v);

    bool operator==(const Vector2& v) const;
    bool operator!=(const Vector2& v) const;
    bool operator>(const Vector2& v) const;
    bool operator>=(const Vector2& v) const;
    bool operator<(const Vector2& v) const;
    bool operator<=(const Vector2& v) const;
    void operator=(const Vector2& v);
    void operator+=(const Vector2& v);
    void operator-=(const Vector2& v);
    void operator*=(const Vector2& v);
    void operator/=(const Vector2& v);
    Vector2 operator+(const Vector2& v) const;
    Vector2 operator-(const Vector2& v) const;
    Vector2 operator*(const Vector2& v) const;
    Vector2 operator*(const float& f) const;
    Vector2 operator/(const Vector2& v) const;


    Vector3 ToVector3();
};

struct Vector3
{
    //Coordinates, Rotation, Relative Direction
    union{float x, pitch, direct;};
    union{float y, yaw, vertical;};
    union{float z, roll, side;};

    Vector3();
    Vector3(float x, float y, float z);
    Vector3(const Vector3& v);
    
    bool operator==(const Vector3& v) const;
    bool operator!=(const Vector3& v) const;
    bool operator>(const Vector3& v) const;
    bool operator>=(const Vector3& v) const;
    bool operator<(const Vector3& v) const;
    bool operator<=(const Vector3& v) const;
    void operator=(const Vector3& v);
    void operator+=(const Vector3& v);
    void operator-=(const Vector3& v);
    void operator*=(const Vector3& v);
    void operator/=(const Vector3& v);
    Vector3 operator+(const Vector3& v) const;
    Vector3 operator-(const Vector3& v) const;
    Vector3 operator*(const Vector3& v) const;
    Vector3 operator*(const float f) const;
    Vector3 operator/(const Vector3& v) const;

    Vector2 ToVector2();
};

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
};

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
};

struct Vertex
{
    Vector3 vector;
    Color color;
    TextureCoords texture_coords;

    Vertex();
    Vertex(Vector3 vector, Color color);
    Vertex(Vector2 vector, Color color);
    Vertex(Vector3 vector, TextureCoords texture_coords);
    Vertex(Vector2 vector, TextureCoords texture_coords);
    Vertex(Vector3 vector, Color color, TextureCoords texture_coords);
    Vertex(Vector2 vector, Color color, TextureCoords texture_coords);
    Vertex(const Vertex& v);
    
    bool operator==(const Vertex& v) const;
    bool operator!=(const Vertex& v) const;
    bool operator>(const Vertex& t) const;
    bool operator>=(const Vertex& t) const;
    bool operator<(const Vertex& t) const;
    bool operator<=(const Vertex& t) const;
    void operator=(const Vertex& v);
    void operator+=(const Vertex& v);
    void operator-=(const Vertex& v);
    void operator*=(const Vertex& v);
    void operator/=(const Vertex& v);
    Vertex operator+(const Vertex& v) const;
    Vertex operator-(const Vertex& v) const;
    Vertex operator*(const Vertex& v) const;
    Vertex operator/(const Vertex& v) const;
};

#endif