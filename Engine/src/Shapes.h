#ifndef SHAPES_H
#define SHAPES_H

#include "Common/Color.h"
#include "Common/TextureCoords.h"
#include "Common/Vector2.h"
#include "Common/Vector3.h"
#include "Common/Vertex.h"

#include "Actor.h"

//Shape and shape_index are for setting triangles of different vertices
//ColTex Color + TextureCoords

template<class V, class ColTex>
std::vector<Vertex> Triangle(V a, V b, V c, ColTex coltex, std::vector<Vertex>& shape, size_t shape_index)
{
    if((typeid(V) != typeid(Vector2) && typeid(V) != typeid(Vector3)) || 
        (typeid(ColTex) != typeid(Color) && typeid(ColTex) != typeid(TextureCoords)))
    {
        return std::vector<Vertex>(0);
    }

    std::vector<Vertex> vertices = std::vector<Vertex>(3);

    vertices[0] = Vertex(a, coltex);
    vertices[1] = Vertex(b, coltex);
    vertices[2] = Vertex(c, coltex);

    shape[shape_index] = Vertex(a, coltex);
    shape[shape_index + 1] = Vertex(b, coltex);
    shape[shape_index + 2] = Vertex(c, coltex);

    return vertices;
};

std::array<Vertex, 6> Square(Vector2 origin, float size, float z_depth, Color color);
std::array<Vertex, 6> Square(Vector2 origin, float size, float z_depth, TextureCoords tex_coords, uint tex_id);
std::array<Vertex, 6> Square(Vector2 origin, float size, float z_depth, std::array<Color, 6> colors);
std::array<Vertex, 6> Square(Vector2 origin, float size, float z_depth, std::array<TextureCoords, 6> tex_coords, uint tex_id);
std::array<Vertex, 6> Square(Vector2 origin, float size, float z_depth, Color color, std::array<TextureCoords, 6> tex_coords, 
    u16 tex_id);

std::array<Vertex, 6> Rectangle(Vector2 origin, float width, float height, float z_depth, Color color);
std::array<Vertex, 6> Rectangle(Vector2 origin, float width, float height, float z_depth, TextureCoords tex_coords, uint tex_id);
std::array<Vertex, 6> Rectangle(Vector2 origin, float width, float height, float z_depth, std::array<Color, 6> colors);
std::array<Vertex, 6> Rectangle(Vector2 origin, float width, float height, float z_depth,
    std::array<TextureCoords, 6> tex_coords, uint tex_id);
std::array<Vertex, 6> Rectangle(Vector2 origin, float width, float height, float z_depth, Color color, 
    std::array<TextureCoords, 6> tex_coords, u16 tex_id);

template<class ColTex>
std::vector<Vertex> Circle(float radius, int triangles, ColTex coltex, std::vector<Vertex>& shape, size_t shape_index)
{
    if(typeid(ColTex) != typeid(Color) && typeid(ColTex) != typeid(TextureCoords))
    {
        return std::vector<Vertex>(0);
    }

    std::vector<Vertex> circle = std::vector<Vertex>(triangles * 3);
    Vector2 center = Vector2(0, 0);
    Vector2 first_point;
    Vector2 second_point;
    float radian = 0;

    int i = 0;
    while(i < triangles)
    {
        first_point.x = cos(radian) * radius;
        first_point.y = sin(radian) * radius;

        radian += (2 * M_PI) / triangles;
        second_point.x = cos(radian) * radius;
        second_point.y = sin(radian) * radius;

        Triangle(center, first_point, second_point, coltex, circle, i * 3);
        shape[shape_index] = Vertex(center, coltex);
        shape[shape_index + 1] = Vertex(first_point, coltex);
        shape[shape_index + 2] = Vertex(second_point, coltex);
        
        i++;
    }

    return circle;
};

//===============================================================================================================
template<class ColTex>
Shared<Model> Cube(float size, ColTex coltex, Vector3 origin = Vector3(0, 0, 0))
{
    if(typeid(ColTex) != typeid(Color) && typeid(ColTex) != typeid(TextureCoords))
    {
        return nullptr;
    }

    std::vector<Vertex> vertices = std::vector<Vertex>(36);
    
    const Vector3 X = origin + Vector3(size, 0, 0);
    const Vector3 Y = origin + Vector3(0, size, 0);
    const Vector3 Z = origin + Vector3(0, 0, size);
    const Vector3 XY = origin + Vector3(size, size, 0);
    const Vector3 XZ = origin + Vector3(size, 0, size);
    const Vector3 YZ = origin + Vector3(0, size, size);
    const Vector3 XYZ = origin + Vector3(size, size, size);
    
    //Front Side
    Triangle(origin, X, XY, coltex, vertices, 0);
    Triangle(origin, Y, XY, coltex, vertices, 3);
    
    //Back Side
    Triangle(Z, XZ, XYZ, coltex, vertices, 6);
    Triangle(Z, YZ, XYZ, coltex, vertices, 9);
    
    //Right Side
    Triangle(X, XZ, XYZ, coltex, vertices, 12);
    Triangle(X, XY, XYZ, coltex, vertices, 15);
    
    //Left Side
    Triangle(origin, Y, YZ, coltex, vertices, 18);
    Triangle(origin, Z, YZ, coltex, vertices ,21);

    //Top Side
    Triangle(Y, YZ, XYZ, coltex, vertices, 24);
    Triangle(Y, XY, XYZ, coltex, vertices, 27);

    //Bottom Side
    Triangle(origin, Z, XZ, coltex, vertices, 30);
    Triangle(origin, X, XZ, coltex, vertices, 33);

    Shared<Model> cube = CreateShared<Model>(vertices);
    return cube;
};

template<class ColTex>
Shared<Model> Prism(float x, float y, float z, ColTex coltex, Vector3 origin = Vector3(0, 0, 0))
{
    if(typeid(ColTex) != typeid(Color) && typeid(ColTex) != typeid(TextureCoords))
    {
        return nullptr;
    }

    std::vector<Vertex> vertices = std::vector<Vertex>(36);
    
    const Vector3 X = origin + Vector3(x, 0, 0);
    const Vector3 Y = origin + Vector3(0, y, 0);
    const Vector3 Z = origin + Vector3(0, 0, z);
    const Vector3 XY = origin + Vector3(x, y, 0);
    const Vector3 XZ = origin + Vector3(x, 0, z);
    const Vector3 YZ = origin + Vector3(0, y, z);
    const Vector3 XYZ = origin + Vector3(x, y, z);
    
    //Front Side
    Triangle(origin, X, XY, coltex, vertices, 0);
    Triangle(origin, Y, XY, coltex, vertices, 3);
    
    //Back Side
    Triangle(Z, XZ, XYZ, coltex, vertices, 6);
    Triangle(Z, YZ, XYZ, coltex, vertices, 9);
    
    //Right Side
    Triangle(X, XZ, XYZ, coltex, vertices, 12);
    Triangle(X, XY, XYZ, coltex, vertices, 15);
    
    //Left Side
    Triangle(origin, Y, YZ, coltex, vertices, 18);
    Triangle(origin, Z, YZ, coltex, vertices ,21);

    //Top Side
    Triangle(Y, YZ, XYZ, coltex, vertices, 24);
    Triangle(Y, YZ, XYZ, coltex, vertices, 27);

    //Bottom Side
    Triangle(origin, Z, XZ, coltex, vertices, 30);
    Triangle(origin, X, XZ, coltex, vertices, 33);

    Shared<Model> prism = CreateShared<Model>(vertices);
    return prism;
};

template<class ColTex>
Shared<Model> Pyramid4(Vector3 a, Vector3 b, Vector3 c, Vector3 d, ColTex coltex)
{
    if(typeid(ColTex) != typeid(Color) && typeid(ColTex) != typeid(TextureCoords))
    {
        return nullptr;
    }

    std::vector<Vertex> vertices = std::vector<Vertex>(0);

    Triangle(a, b, c, coltex, vertices, 0);
    Triangle(a, b, d, coltex, vertices, 3);
    Triangle(a, c, d, coltex, vertices, 6);
    Triangle(b, c, d, coltex, vertices, 9);

    Shared<Model> pyramid = CreateShared<Model>(vertices);
    return pyramid;
};

template<class ColTex>
Shared<Model> Cylinder(float radius, float height, int triangles, ColTex coltex)
{
    if(typeid(ColTex) != typeid(Color) && typeid(ColTex) != typeid(TextureCoords))
    {
        return nullptr;
    }

    std::vector<Vertex> vertices = std::vector<Vertex>(triangles * 24);
    Circle(radius, triangles, coltex, vertices, 0);
    Circle(radius, triangles, coltex, vertices, 24);

    int i = 0;
    while(i < triangles)
    {
        Triangle(vertices[i + 1].vector, vertices[i + 2].vector, vertices[i + 25].vector, coltex, vertices, i + 48);
        Triangle(vertices[i + 1].vector, vertices[i + 2].vector, vertices[i + 26].vector, coltex, vertices, i + 49);
        i++;
    }

    Shared<Model> cylinder = CreateShared<Model>(vertices);
    return cylinder;
};

/*template<class ColTex>
void FillAllTriangles(Shared<Model> model, ColTex coltex)
{
    if(typeid(ColTex) != typeid(Color) && typeid(ColTex) != typeid(TextureCoords))
    {
        return nullptr;
    }

    for(int i = 0; i < model->vertices.size(); i += 3)
    {
        Triangle(model->vertices[i], model->vertices[i + 1], model->vertices[i + 2], coltex, model->vertices, i);
    }
}*/
#endif