#ifndef VECTOR3_H
#define VECTOR3_H

struct Vector2;

/*
 * This Engine Follows A Left Hand Coordinate System
 * Index Finger Is X, Thumb Is Y, Middle Is Z
 * [direct], [side], And [vertical] Are Relative Directions
 */

struct Vector3
{
    //Coordinates, Rotation, Relative Direction
    union{float x, pitch, direct;};
    union{float y, yaw, vertical;};
    union{float z, roll, side;};

    Vector3();
    Vector3(float x, float y, float z);
    Vector3(Vector2 xy, float z);
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
    static std::vector<Vector3> ToVectorArray(const float* points);
};
#endif
