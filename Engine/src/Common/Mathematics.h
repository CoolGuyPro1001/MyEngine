#ifndef MATH_H
#define MATH_H

struct Vector2;
struct Vector3;

bool GaussJordan(std::vector<std::vector<float>>& a);
float DotProduct(Vector2 a, Vector2 b);
float DotProduct(Vector3 a, Vector3 b);
Vector3 CrossProduct(Vector3 a, Vector3 b);

float Vector2Magnitude(Vector2 a);
float Vector3Magnitude(Vector3 a);
Vector2 NormalizeVector2(Vector2 a);
Vector3 NormalizeVector3(Vector3 a);

Vector3 Intersect3DSegments(const Vector3 a0, const Vector3 a1, const Vector3 b0, const Vector3 b1, bool& intersected);
bool InSegment(Vector2 p, Vector2 s0, Vector2 s1);
bool InsideOutTest(Vector3 point, Vector3 t0, Vector3 t1, Vector3 t2, Vector3 n);
bool IntersectRayTriangle(const Vector3 origin, const Vector3 dir, const Vector3 t0, const Vector3 t1, const Vector3 t2, 
    const Vector3 n, Vector3& intersect, float& t);
bool IntersectParallelpipedTriangle(const Vector3 origin, const Vector3 dir, const Vector3 width, const Vector3 height, 
    const Vector3 t0, const Vector3 t1, const Vector3 t2, const Vector3 n, Vector3& intersect, float& m);

float Normalize(float num, float low, float high);

float DegreesToRadians(float degrees);

enum IntersectResults
{
    NOT,
    INTERSECT,
    OVERLAP
};

IntersectResults IntersectSegments(Vector2 a0, Vector2 a1, Vector2 b0, Vector2 b1, Vector2 p1, Vector2 p2);

#endif
