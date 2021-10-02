#include "Vector2.h"

Vector2::Vector2()
{
    x, y = 0;
}

Vector2::Vector2(float x, float y) : x(x), y(y)
{
}

Vector2::Vector2(const Vector2& v) 
{
    x = v.x;
    y = v.y;
}

bool Vector2::operator==(const Vector2& v) const
{
    return v.x == x && v.y == y;
}

bool Vector2::operator!=(const Vector2& v) const
{
    return v.x != x || v.y != y;
}

bool Vector2::operator>(const Vector2& v) const
{
    return x > v.x && y > v.y;
}

bool Vector2::operator>=(const Vector2& v) const
{
    return x >= v.x && y >= v.y;
}

bool Vector2::operator<(const Vector2& v) const
{
    return x < v.x && y < v.y;
}

bool Vector2::operator<=(const Vector2& v) const
{
    return x <= v.x && y <= v.y;
}

void Vector2::operator=(const Vector2& v)
{
    x = v.x;
    y = v.y;
}

void Vector2::operator+=(const Vector2& v)
{
    x += v.x;
    y += v.y;
}

void Vector2::operator-=(const Vector2& v)
{
    x -= v.x;
    y -= v.y;
}

void Vector2::operator*=(const Vector2& v)
{
    x *= v.x;
    y *= v.y;
}

void Vector2::operator/=(const Vector2& v)
{
    x /= v.x;
    y /= v.y;
}

Vector2 Vector2::operator+(const Vector2& v) const
{
    return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const Vector2& v) const
{
    return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator*(const Vector2& v) const
{
    return Vector2(x * v.x, y * v.y);
}

Vector2 Vector2::operator*(const float& f) const
{
    return Vector2(x * f, y * f);
}

Vector2 Vector2::operator/(const Vector2& v) const
{
    return Vector2(x / v.x, y / v.y);
}

std::vector<Vector2> Vector2::ToVectorArray(const float* points)
{
    size_t vectors_size = sizeof(points) / sizeof(Vector2);
    Vector2 vectors[vectors_size];

    memcpy(vectors, points, sizeof(points));

    return std::vector<Vector2>(vectors, vectors + vectors_size);
}