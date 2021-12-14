#ifndef VECTOR2_H
#define VECTOR2_H

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

    static std::vector<Vector2> ToVectorArray(const float* points);
};
#endif
