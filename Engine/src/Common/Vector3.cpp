#include "Vector3.h"
#include "Vector2.h"

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
    x /= v.x;
    y /= v.y;
    z /= v.z;
}

Vector3 Vector3::operator+(const Vector3& v) const
{
    return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator-(const Vector3& v) const
{
    return Vector3(x - v.x, y - v.y, z - v.z);
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
    return Vector3(x / v.x, y / v.y, z / v.z);
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
