#include "Vector3.h"
#include "Vector2.h"

#include "Common/Error.h"

Vector3::Vector3()
{
    x = 0;
    y = 0;
    z = 0;
}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z)
{
}

Vector3::Vector3(Vector2 xy, float z) : x(xy.x), y(xy.y), z(z)
{
}

Vector3::Vector3(const Vector3& v) 
{
    x = v.x;
    y = v.y;
    z = v.z;
}

bool Vector3::operator==(const Vector3& v) const
{
    return v.x == x && v.y == y && v.z == z;
}

bool Vector3::operator!=(const Vector3& v) const
{
    return v.x != x || v.y != y || v.z != z;
}

bool Vector3::operator>(const Vector3& v) const
{
    return x > v.x && y > v.y && z > v.z;
}

bool Vector3::operator>=(const Vector3& v) const
{
    return x >= v.x && y >= v.y && z >= v.z;
}

bool Vector3::operator<(const Vector3& v) const
{
    return x < v.x && y < v.y && z < v.z;
}

bool Vector3::operator<=(const Vector3& v) const
{
    return x <= v.x && y <= v.y && z <= v.z;
}

void Vector3::operator=(const Vector3& v)
{
    x = v.x;
    y = v.y;
    z = v.z;
}

void Vector3::operator+=(const Vector3& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
}

void Vector3::operator-=(const Vector3& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
}

void Vector3::operator*=(const Vector3& v)
{
    x *= v.x;
    y *= v.y;
    z *= v.z;
}

void Vector3::operator/=(const Vector3& v)
{
    auto divide_by_zero_error = [=](char c)
    {
        CriticalErrorArgs(ENGINE_ERROR, "Can't Divide Texture Coordinate %c By 0. Setting %c To 0\n", c);
        return 1;
    };

    x /= (x != 0) ? v.x : divide_by_zero_error('X');
    y /= (y != 0) ? v.y : divide_by_zero_error('Y');
    z /= (z != 0) ? v.z : divide_by_zero_error('Z');
}

Vector3 Vector3::operator+(const Vector3& v) const
{
    return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator-(const Vector3& v) const
{
    return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator-() const
{
    return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator*(const Vector3& v) const
{
    return Vector3(x * v.x, y * v.y, z * v.z);
}

Vector3 Vector3::operator*(const float f) const
{
    return Vector3(x * f, y * f, z * f);
}

Vector3 Vector3::operator/(const Vector3& v) const
{
    float temp_x = x;
    float temp_y = y;
    float temp_z = z;

    auto divide_by_zero_error = [=](char c)
    {
        CriticalErrorArgs(ENGINE_ERROR, "Can't Divide Vector3 Coordinate %c By 0. Returning Original Value\n", c);
        return 1;
    };

    temp_x /= (v.x != 0) ? v.x : divide_by_zero_error('X');
    temp_y /= (v.y != 0) ? v.y : divide_by_zero_error('Y');
    temp_z /= (v.z != 0) ? v.z : divide_by_zero_error('Z');

    return Vector3(temp_x, temp_y, temp_z);
}

Vector2 Vector3::ToVector2()
{
    return Vector2(x, y);
}

std::vector<Vector3> Vector3::ToVectorArray(const float* points)
{
    size_t vectors_size = sizeof(points) / sizeof(Vector3);
    Vector3 vectors[vectors_size];

    memcpy(vectors, points, sizeof(points));

    return std::vector<Vector3>(vectors, vectors + vectors_size);
}
