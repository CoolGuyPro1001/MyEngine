#include "Units.h"

Vector3::Vector2(float x, float y) : x(x), y(y)
{

}

Vector3::Vector2()
{

}

void Vector2::operator=(const Vector2& v)
{
    x = v.x;
    y = v.y;
}

bool Vector2::operator==(Vector2& v)
{
    if(v.x == x && v.y == y)
        return true;
    else
        return false;
}

bool Vector2::operator!=(Vector2& v)
{
    if(v.x != x || v.y != y)
        return true;
    else
        return false;
}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z)
{

}

Vector3::Vector3()
{

}

void Vector3::operator=(const Vector3& v)
{
    x = v.x;
    y = v.y;
    z = v.z;
}

bool Vector3::operator==(Vector3& v)
{
    if(v.x == x && v.y == y && v.z == z)
        return true;
    else
        return false;
}

bool Vector3::operator!=(Vector3& v)
{
    if(v.x != x || v.y != y || v.z == z)
        return true;
    else
        return false;
}

Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) 
{

}

Color::Color()
{

}

void Color::operator=(const Color& c)
{
    r = c.r;
    g = c.g;
    b = c.b;
    a = c.a;
}

bool Color::operator==(Color& c)
{
    if(c.r == r && c.g == g && c.b == b && c.a == a)
        return true;
    else
        return false;
}

bool Color::operator!=(Color& c)
{
    if(c.r != r || c.g != g || c.b != b || c.a != a)
        return true;
    else
        return false;
}

Vertex::Vertex(Vector3 vector, Color color) : vector(vector), color(color) 
{

}

void Vertex::operator=(const Vertex& v)
{
    vector = v.vector;
    color = v.color;
}

bool Vertex::operator==(Vertex& v)
{
    if(v.vector == vector && v.color == color)
        return true;
    else
        return false;
}

bool Vertex::operator!=(Vertex& v)
{
    if(v.vector != vector || v.color != color)
        return true;
    else
        return false;
}