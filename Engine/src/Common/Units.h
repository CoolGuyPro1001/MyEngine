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
    float x, y, z;

    Vector3(float x, float y, float z);
    Vector3();

    void operator=(const Vector3& v);
    bool operator==(const Vector3& v) const;
    bool operator!=(const Vector3& v) const;
    Vector3 operator+(const Vector3& v) const;

    Vector2 ToVector2();
};

struct Color
{
    float r, g, b, a;

    Color(float r, float g, float b, float a);
    Color();

    void operator=(const Color& c);
    bool operator==(const Color& c) const;
    bool operator!=(const Color& c) const;
};

struct Vertex
{
    Vector3 vector;
    Color color;

    Vertex();
    Vertex(Vector3 vector, Color color);
    Vertex(Vector2 vector, Color color);
    
    void operator =(const Vertex& v);
    bool operator ==(const Vertex& v) const;
    bool operator !=(const Vertex& v) const;
};

#endif