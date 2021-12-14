#ifndef SHAPES_H
#define SHAPES_H

#include "Vector3.h"

struct Vertex;
struct Vector2;
struct TextureCoord;
struct Color;
struct CModel;
struct ModelTexture;

//Shape and shape_index are for setting triangles of different vertices
//ColTex Color + TextureCoord

std::vector<Vertex> Triangle(Vector3 p0, Vector3 p1, Vector3 p2, Color color, std::vector<Vertex>& shape, size_t shape_index);
std::vector<Vertex> Triangle(Vector3 p0, Vector3 p1, Vector3 p2, TextureCoord uv0, TextureCoord uv1,
    TextureCoord uv2, uint texture_id, std::vector<Vertex>& shape, size_t shape_index);

std::array<Vertex, 6> Square(Vector2 origin, float size, float z_depth, Color color);
std::array<Vertex, 6> Square(Vector2 origin, float size, float z_depth, TextureCoord tex_coords, uint tex_id);
std::array<Vertex, 6> Square(Vector2 origin, float size, float z_depth, std::array<Color, 6> colors);
std::array<Vertex, 6> Square(Vector2 origin, float size, float z_depth, std::array<TextureCoord, 6> tex_coords, uint tex_id);
std::array<Vertex, 6> Square(Vector2 origin, float size, float z_depth, Color color, std::array<TextureCoord, 6> tex_coords,
    u16 tex_id);

std::array<Vertex, 6> Rectangle(Vector2 origin, float width, float height, float z_depth, Color color);
std::array<Vertex, 6> Rectangle(Vector2 origin, float width, float height, float z_depth, TextureCoord tex_coords, uint tex_id);
std::array<Vertex, 6> Rectangle(Vector2 origin, float width, float height, float z_depth, std::array<Color, 6> colors);

std::array<Vertex, 6> Rectangle(Vector2 origin, float width, float height, float z_depth,
    std::array<TextureCoord, 6> tex_coords, uint tex_id);

std::array<Vertex, 6> Rectangle(Vector2 origin, float width, float height, float z_depth, Color color, 
    std::array<TextureCoord, 6> tex_coords, u16 tex_id);

std::vector<Vertex> Circle(float radius, int triangles, Color color, std::vector<Vertex>& shape, size_t shape_index);

//===============================================================================================================
Shared<CModel> Cube(float size, Color front, Color back, Color left, Color right, Color top, Color bottom,
    Vector3 origin = Vector3(0, 0, 0));

Shared<CModel> Cube(float size,
    Shared<ModelTexture> front, Shared<ModelTexture> back,
    Shared<ModelTexture> left, Shared<ModelTexture> right,
    Shared<ModelTexture> top, Shared<ModelTexture> bottom,
    Vector3 origin = Vector3(0, 0, 0));

Shared<CModel> Prism(float x, float y, float z, Color color, Vector3 origin = Vector3(0, 0, 0));

Shared<CModel> Prism(float x, float y, float z,
    Shared<ModelTexture> front, Shared<ModelTexture> back,
    Shared<ModelTexture> left, Shared<ModelTexture> right,
    Shared<ModelTexture> top, Shared<ModelTexture> bottom,
    Vector3 origin = Vector3(0, 0, 0));


Shared<CModel> Pyramid4(Vector3 a, Vector3 b, Vector3 c, Vector3 d, Color color);
Shared<CModel> Cylinder(float radius, float height, int triangles, Color color);
#endif
