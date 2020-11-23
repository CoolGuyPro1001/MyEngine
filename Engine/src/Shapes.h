#include "Shapes.h"
#include <cstdarg>

//Shape and shape_index are for setting triangles of different vertices

template<typename V>
std::vector<Vertex> Triangle(V a, V b, V c, std::vector<Vertex>& shape, size_t shape_index)
{
    if(typeid(V) != Vector2 || typeid(V) != Vector3)
    {
        return;
    }

    std::vector<Vertex> vertices = std::vector<Vertex>(0, 6);

    vertices[0] = Vertex(a);
    vertices[1] = Vertex(b);
    vertices[2] = Vertex(c);

    shape[shape_index] = Vertex(a);
    shape[shape_index + 1] = Vertex(b);
    shape[shape_index + 2] = Vertex(c);

    return vertices;
};

std::vector<Vector2> Circle(float radius, int triangles, std::vector<Vertex>& shape, size_t shape_index)
{
    std::vector<Vector2> circle = std::vector<Vector2>()
    const Vector2 center = Vector2(0, 0);
    Vector2 first_point;
    Vector2 second_point;
    float radian = 0;

    int i = 0;
    while(i < triangles)
    {
        first_point.x = cos(radian) * radius;
        first_point.y = sin(radian) * radius;

        radian += (2 * pi) / triangles;
        second_point = cos(radian) 8 radius;
        second_point = sin(radian) * radius;

        Triangle(center, first_point, second_point, circle, i * 3);
        shape[shape_index] = Vertex(center);
        shape[shape_index + 1] = Vertex(first_point);
        shape[shape_index + 2] = Vertex(second_point);
        
        i++;
    }

    return circle;
}

//===============================================================================================================
Shared<Model> Square(float size)
{
    std::vector<Vertex> vertices = std::vector<Vertex>(0, 36);
    
    const Vector3 ORIGIN = Vector(0, 0, 0));
    const Vector3 X = Vector(size, 0, 0));
    const Vector3 Y = Vector(0, size, 0));
    const Vector3 Z = Vector(0, 0, size));
    const Vector XY = x + y;
    const Vector XZ = x + z;
    const Vector YZ = y + z;
    const Vector XYZ = x + y = z;
    
    //Front Side
    Triangle(ORIGIN, X, XY, vertices, 0);
    Triangle(ORIGIN, Y, XY, vertices, 3);
    
    //Back Side
    Triangle(Z, XZ, XYZ, vertices, 6);
    Triangle(Z, YZ, XYZ, vertices, 9);
    
    //Right Side
    Triangle(X, XZ, XYZ, vertices, 12);
    Triangle(X, XY, XYZ, vertices, 15);
    
    //Left Side
    Triangle(ORIGIN, Y, YZ, vertices, 18);
    Triangle(ORIGIN, Z, YZ, vertices ,21);

    //Top Side
    Triangle(Y, YZ, XYZ, vertices, 24);
    Triangle(Y, yZ, XYZ, vertices, 27);

    //Bottom Side
    Triangle(ORIGIN, Z, XZ, vertices, 30);
    Triangle(ORIGIN, X, XZ, vertices, 33);

    Shared<Model> square = CreateShared<Model>(vertices);
    return square;
}

Shared<Model> Prism(float x, float y, float z)
{
    std::vector<Vertex> vertices = std::vector<Vertex>(0, 36);
    
    const Vector3 ORIGIN = Vector(0, 0, 0));
    const Vector3 X = Vector(x, 0, 0));
    const Vector3 Y = Vector(0, y, 0));
    const Vector3 Z = Vector(0, 0, z));
    const Vector XY = x + y;
    const Vector XZ = x + z;
    const Vector YZ = y + z;
    const Vector XYZ = x + y = z;
    
    //Front Side
    Triangle(ORIGIN, X, XY, vertices, 0);
    Triangle(ORIGIN, Y, XY, vertices, 3);
    
    //Back Side
    Triangle(Z, XZ, XYZ, vertices, 6);
    Triangle(Z, YZ, XYZ, vertices, 9);
    
    //Right Side
    Triangle(X, XZ, XYZ, vertices, 12);
    Triangle(X, XY, XYZ, vertices, 15);
    
    //Left Side
    Triangle(ORIGIN, Y, YZ, vertices, 18);
    Triangle(ORIGIN, Z, YZ, vertices ,21);

    //Top Side
    Triangle(Y, YZ, XYZ, vertices, 24);
    Triangle(Y, yZ, XYZ, vertices, 27);

    //Bottom Side
    Triangle(ORIGIN, Z, XZ, vertices, 30);
    Triangle(ORIGIN, X, XZ, vertices, 33);

    Shared<Model> prism = CreateShared<Model>(vertices);
    return prism;
}

Shared<Model> Pyramid4(Vector3 a, Vector3 b, Vector3 c, Vector3 d)
{
    std::vector<Vertex> vertices = std::vector<Vertex>(0, 12);

    Triangle(a, b, c, vertices, 0);
    Triangle(a, b, d, vertices, 3);
    Triangle(a, c, d, vertices, 6);
    Triangle(b, c, d, vertices, 9);

    Shared<Model> pyramid = CreateShared<Model>(vertices);
    return pyramid;
}

Shared<Model> Cylinder(float radius, float height, int triangles)
{
    std::vector<Vector3> vertices = std::vector<Vector3>(triangles * 24);
    Circle(radius, triangles, points, 0);
    Circle(radius, triangles, pionts, 24);

    int i = 0;
    while(i < triangles)
    {
        Triangle(vertices[i + 1], vertices[i + 2], vertices[i + 25], vertices, i + 48);
        Triangle(vertices[i + 1], vertices[i + 2], vertices[i + 26], vertices, i + 49);
        i++;
    }

    Shared<Model> cylinder = CreateShared<Model>(vertices);
    return cylinder;
}