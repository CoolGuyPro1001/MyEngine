#include "Vector2.h"

#include "Common/Error.h"

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
    auto divide_by_zero_error = [=](char c)
    {
        CriticalErrorArgs(ENGINE_ERROR, "Can't Divide Texture Coordinate %c By 0. Setting %c To 0\n", c);
        return 1;
    };

    x /= (x != 0) ? v.x : divide_by_zero_error('X');
    y /= (y != 0) ? v.y : divide_by_zero_error('Y');
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
    float temp_x = x;
    float temp_y = y;

    auto divide_by_zero_error = [=](char c)
    {
        CriticalErrorArgs(ENGINE_ERROR, "Can't Divide Vector2 Coordinate %c By 0. Returning Original Value\n", c);
        return 1;
    };

    temp_x /= (v.x != 0) ? v.x : divide_by_zero_error('X');
    temp_y /= (v.y != 0) ? v.y : divide_by_zero_error('Y');

    return Vector2(temp_x, temp_y);
}

std::vector<Vector2> Vector2::ToVectorArray(const float* points)
{
    size_t vectors_size = sizeof(points) / sizeof(Vector2);
    Vector2 vectors[vectors_size];

    memcpy(vectors, points, sizeof(points));

    return std::vector<Vector2>(vectors, vectors + vectors_size);
}
