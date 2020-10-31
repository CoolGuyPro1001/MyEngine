#ifndef UNITS_H
#define UNITS_H

struct Vector2
{
    float x, y;

    Vector2(float x, float y);
    Vector2();

    void operator =(const Vector2& v);
    bool operator ==(Vector2& v);
    bool operator !=(Vector2& v);
};

struct Vector3
{
    float x, y, z;

    Vector3(float x, float y, float z);
    Vector3();

    void operator =(const Vector3& v);
    bool operator ==(Vector3& v);
    bool operator !=(Vector3& v);
};

struct Color
{
    float r, g, b, a;

    Color(float r, float g, float b, float a);
    Color();

    void operator =(const Color& c);
    bool operator ==(Color& c);
    bool operator !=(Color& c);
};

struct Vertex
{
    Vector3 vector;
    Color color;

    Vertex(Vector3 vector, Color color);

    void operator =(const Vertex& v);
    bool operator ==(Vertex& v);
    bool operator !=(Vertex& v);
};

#endif