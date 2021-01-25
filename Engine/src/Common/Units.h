#ifndef UNITS_H
#define UNITS_H

struct Vector2;
struct Vector3;

struct Vector2
{
    float x, y;

    Vector2(float x, float y);
    Vector2();

    void operator=(const Vector2& v);
    bool operator==(const Vector2& v) const;
    bool operator!=(const Vector2& v) const;
    Vector2 operator+(const Vector2& v) const;

    Vector3 ToVector3();
};

struct Vector3
{
    union{float x, pitch;};
    union{float y, yaw;};
    union{float z, roll;};

    Vector3(float x, float y, float z);
    Vector3();

    void operator=(const Vector3& v);
    bool operator==(const Vector3& v) const;
    bool operator!=(const Vector3& v) const;
    Vector3 operator+(const Vector3& v) const;
    void operator+=(const Vector3& v);

    Vector2 ToVector2();
};

struct Color
{
    u8 r, g, b, a;

    Color(u8 r, u8 g, u8 b, u8 a);
    Color();

    void operator=(const Color& c);
    bool operator==(const Color& c) const;
    bool operator!=(const Color& c) const;
};

struct TextureCoords
{
    float u, v;

    TextureCoords(float u, float v);
    TextureCoords();

    void operator=(const TextureCoords& t);
    bool operator==(const TextureCoords& t) const;
    bool operator!=(const TextureCoords& t) const;
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
    
    void operator =(const Vertex& v);
    bool operator ==(const Vertex& v) const;
    bool operator !=(const Vertex& v) const;
};

#endif