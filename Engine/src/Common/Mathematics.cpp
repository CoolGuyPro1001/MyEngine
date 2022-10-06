#include "Mathematics.h"

#include "Error.h"
#include "Vector2.h"
#include "Vector3.h"

float DotProduct(Vector2 a, Vector2 b)
{
    return (a.x * b.x) + (a.y * b.y);
}

float DotProduct(Vector3 a, Vector3 b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

Vector3 CrossProduct(Vector3 a, Vector3 b)
{
    Vector3 cross;
    cross.x = (a.y * b.z - a.z * b.y);
    cross.y = -(a.x * b.z - a.z * b.x);
    cross.z = (a.x * b.y - a.y * b.x);
    return cross;
}

float Vector2Magnitude(Vector2 a)
{
    return sqrt(pow(a.x, 2.0f) + pow(a.y, 2.0f));
}

float Vector3Magnitude(Vector3 a)
{
    return sqrt(pow(a.x, 2.0f) + pow(a.y, 2.0f) + pow(a.z, 2.0f));
}

Vector2 NormalizeVector2(Vector2 a)
{
    float mag = Vector2Magnitude(a);

    if(mag == 0)
        CriticalError(ENGINE_ERROR, "Magnitude Is 0 (Will Generate A Divide By 0 Error)\n");

    return Vector2(a.x / mag, a.y / mag);
}

Vector3 NormalizeVector3(Vector3 a)
{
    float mag = Vector3Magnitude(a);

    if(mag == 0)
        CriticalError(ENGINE_ERROR, "Magnitude Is 0 (Will Generate A Divide By 0 Error)\n");

    return Vector3(a.x / mag, a.y / mag, a.z / mag);
}

bool InSegment(Vector2 p, Vector2 s0, Vector2 s1)
{
    if (s0.x != s1.x) 
    {    // S is not  vertical
        if (s0.x <= p.x && p.x <= s1.x)
            return true;
        if (s0.x >= p.x && p.x >= s1.x)
            return true;
    }
    else 
    {    // S is vertical, so test y  coordinate
        if (s0.y <= p.y && p.y <= s1.y)
            return 1;
        if (s0.y >= p.y && p.y >= s1.y)
            return 1;
    }

    return false;
}

bool GaussJordan(std::vector<std::vector<float>>& a)
{
    int i, j, k = 0, c;
    bool flag = false;
    float pro = 0;

    int n = a.size();
      
    // Performing elementary operations
    for (i = 0; i < n; i++)
    {
        if (a[i][i] == 0) 
        {
            c = 1;
            while ((i + c) < n && a[i + c][i] == 0) 
                c++;            
            if ((i + c) == n) {
                flag = 1;
                break;
            }
            for (j = i, k = 0; k <= n; k++) 
                std::swap(a[j][k], a[j+c][k]);
        }
  
        for (j = 0; j < n; j++) {
              
            // Excluding all i == j
            if (i != j) {
                  
                // Converting Matrix to reduced row
                // echelon form(diagonal matrix)
                float pro = a[j][i] / a[i][i];
  
                for (k = 0; k <= n; k++)                 
                    a[j][k] = a[j][k] - (a[i][k]) * pro;                
            }
        }
    }
    return flag;
}

Vector3 Intersect3DSegments(const Vector3 a0, const Vector3 a1, const Vector3 b0, const Vector3 b1, bool& intersected)
{
    Vector3 intersect;
    std::vector<std::vector<float>> equations = std::vector<std::vector<float>>(3);

    Vector3 a1a0 = a1 - a0;
    Vector3 b1b0 = b1 - b0;
    Vector3 b0a0 = b0 - a0;

    equations[0] = {a1a0.x, b1b0.x, 0, b0a0.x};
    equations[1] = {a1a0.y, b1b0.y, 0, b0a0.y};
    equations[2] = {a1a0.z, b1b0.z, 0, b0a0.z};

    if(GaussJordan(equations))
    {
        float t = equations[0][3];
        intersect = a1 + (b1 - a1) * t;
        intersected = true;
    }

    intersected = false;
    return Vector3(0, 0, 0);
}

//Credits To http://geomalgorithms.com/a05-_intersect-1.html

IntersectResults IntersectSegments(Vector2 a0, Vector2 a1, Vector2 b0, Vector2 b1, Vector2 p0, Vector2 p1)
{
    Vector2 u = a1 - a0;
    Vector2 v = b1 - b0;
    Vector2 w = a0 - b0;
    float D = DotProduct(u, v);


    // test if  they are parallel (includes either being a point)
    if (fabs(D) < 0.00000001) 
    {           // S1 and S2 are parallel
        if (DotProduct(u,w) != 0 || DotProduct(v,w) != 0)
        {
            return NOT;                    // they are NOT collinear
        }

        // they are collinear or degenerate
        // check if they are degenerate  points
        float du = DotProduct(u,u);
        float dv = DotProduct(v,v);

        if (du == 0 && dv == 0) 
        {            // both segments are points
            if (a0 != b0)         // they are distinct  points
                 return NOT;
            p0 = a0;                 // they are the same point
            return INTERSECT;
        }

        if (du == 0) 
        {                     // S1 is a single point
            if  (InSegment(a0, b0, b1) == 0)  // but is not in S2
                 return NOT;
            p0 = a0;
            return INTERSECT;
        }

        if (dv == 0) 
        {                     // S2 a single point
            if  (InSegment(b0, a0, a1) == 0)  // but is not in S1
                 return NOT;
            p0 = b0;
            return INTERSECT;
        }

        //They are collinear segments - get  overlap (or not)
        float t0, t1;                    // endpoints of S1 in eqn for S2
        Vector2 w2 = a1 - b0;

        if (v.x != 0) 
        {
            t0 = w.x / v.x;
            t1 = w2.x / v.x;
        }
        else 
        {
            t0 = w.y / v.y;
            t1 = w2.y / v.y;
        }

        if (t0 > t1) 
        {                   // must have t0 smaller than t1
            float t=t0; t0=t1; t1=t;    // swap if not
        }

        if (t0 > 1 || t1 < 0) 
        {
            return NOT;      // NO overlap
        }

        t0 = (t0 < 0) ? 0 : t0;               // clip to min 0
        t1 = (t1 > 1) ? 1 : t1; // clip to max 1

        if (t0 == t1) 
        {                  // intersect is a point
            p0 = b0 +  v * t0;
            return INTERSECT;
        }

        // they overlap in a valid subsegment
        p0 = b0 + v * t0;
        p1 = b0 + v * t1;
        return OVERLAP;
    }

    // the segments are skew and may intersect in a point
    // get the intersect parameter for S1
    float sI = DotProduct(v,w) / D;
    if (sI < 0 || sI > 1)                // no intersect with S1
        return NOT;

    // get the intersect parameter for S2
    float tI = DotProduct(u,w) / D;
    if (tI < 0 || tI > 1)                // no intersect with S2
        return NOT;

    p0 = a0 + u * sI;                // compute S1 intersect point
    return INTERSECT;
}

bool InsideOutTest(Vector3 point, Vector3 t0, Vector3 t1, Vector3 t2, Vector3 n)
{
    Vector3 C; // vector perpendicular to triangle's plane 
 
    // edge 0
    Vector3 edge0 = t1 - t0; 
    Vector3 vp0 = point - t0; 
    C = CrossProduct(edge0, vp0);
    if (DotProduct(n, C) < 0) 
        return false; // P is on the right side 
 
    // edge 1
    Vector3 edge1 = t2 - t1; 
    Vector3 vp1 = point - t1; 
    C = CrossProduct(edge1, vp1);
    if (DotProduct(n, C) < 0)
        return false; // P is on the right side 
 
    // edge 2
    Vector3 edge2 = t0 - t2; 
    Vector3 vp2 = point - t2; 
    C = CrossProduct(edge2, vp2);
    if (DotProduct(n, C) < 0)
        return false; // P is on the right side;
    
    return true;
}

bool IntersectRayTriangle(const Vector3 origin, const Vector3 dir, const Vector3 t0, const Vector3 t1, const Vector3 t2, 
    const Vector3 n, Vector3& intersect, float& m)
{
    //Is Parallel?
    float direction = DotProduct(NormalizeVector3(n), dir); 
    if (fabs(direction) < EPSILON)
        return false; // Parallel Confirmed

    float d = DotProduct(NormalizeVector3(n), t0);
    float o = -DotProduct(NormalizeVector3(n), origin);
    m = (o + d) / direction;

    if(m < 0)
        return false; // Triangle Is Behind

    intersect = origin + dir * m;

    //i is in plane, checking if it's in triangle
    //Inside-Out Test

    // Step 2: inside-outside test 
    return InsideOutTest(intersect, t0, t1, t2, n);
}

bool IntersectParallelpipedTriangle(const Vector3 origin, const Vector3 dir, const Vector3 width, const Vector3 height, 
    const Vector3 t0, const Vector3 t1, const Vector3 t2, const Vector3 n, Vector3& intersect, float& m)
{
    //Is Parallel?
    float direction = DotProduct(NormalizeVector3(n), dir); 
    if (fabs(direction) < EPSILON)
        return false; // Parallel Confirmed

    float d = DotProduct(NormalizeVector3(n), t0);
    float o = -DotProduct(NormalizeVector3(n), origin);
    m = (o + d) / direction;

    if(m < 0)
        return false;

    intersect = origin + dir * m;
    Vector3 diagonal = intersect + width + height;

    //Bounding Box Test

    //If A Triangle Point Is In Square
    float corner_magnitude = Vector3Magnitude(diagonal - intersect);

    if
    (
        t0.x > std::min(intersect.x, diagonal.x) && t0.x < std::max(intersect.x, diagonal.x) && 
        t0.y > std::min(intersect.y, diagonal.y) && t0.y < std::max(intersect.y, diagonal.y) && 
        t0.z > std::min(intersect.z, diagonal.z) && t0.z < std::max(intersect.z, diagonal.z)
    )
    {
        return true;
    }

    if
    (
        t1.x > std::min(intersect.x, diagonal.x) && t1.x < std::max(intersect.x, diagonal.x) && 
        t1.y > std::min(intersect.y, diagonal.y) && t1.y < std::max(intersect.y, diagonal.y) && 
        t1.z > std::min(intersect.z, diagonal.z) && t1.z < std::max(intersect.z, diagonal.z)
    )
    {
        return true;
    }

    if
    (
        t2.x > std::min(intersect.x, diagonal.x) && t2.x < std::max(intersect.x, diagonal.x) && 
        t2.y > std::min(intersect.y, diagonal.y) && t2.y < std::max(intersect.y, diagonal.y) && 
        t2.z > std::min(intersect.z, diagonal.z) && t2.z < std::max(intersect.z, diagonal.z)
    )
    {
        return true;
    }

    bool overlap = false;

    Intersect3DSegments(t0, t1, intersect, width, overlap);
    Intersect3DSegments(t0, t1, intersect, height, overlap);
    Intersect3DSegments(t0, t1, width, diagonal, overlap);
    Intersect3DSegments(t0, t1, height, diagonal,overlap);

    Intersect3DSegments(t1, t2, intersect, width, overlap);
    Intersect3DSegments(t1, t2, intersect, height, overlap);
    Intersect3DSegments(t1, t2, width, diagonal, overlap);
    Intersect3DSegments(t1, t2, height, diagonal, overlap);

    Intersect3DSegments(t2, t0, intersect, width, overlap);
    Intersect3DSegments(t2, t0, intersect, height, overlap);
    Intersect3DSegments(t2, t0, width, diagonal, overlap);
    Intersect3DSegments(t2, t0, height, diagonal, overlap);

    //If A Square Point Is In Triangle
    if(InsideOutTest(intersect, t0, t1, t2, n))
        return true;
    
    if(InsideOutTest(width, t0, t1, t2, n))
        return true;

    if(InsideOutTest(height, t0, t1, t2, n))
        return true;

    if(InsideOutTest(diagonal, t0, t1, t2, n))
        return true;

    //If Two Edges Intersect
    
    return overlap;
}

float Normalize(float num, float low, float high)
{
    if(num < low)
        return 0;

    if(num > high)
        return 1;

    return (num - low) / (high - low);
}

float DegreesToRadians(float degrees)
{
    return degrees * (PI / 180);
}
