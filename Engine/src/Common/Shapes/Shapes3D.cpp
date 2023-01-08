#include "Common/Shapes.h"

#include "Common/Color.h"
#include "Common/TextureCoord.h"
#include "Common/Vector3.h"
#include "Common/Vertex.h"
#include "Common/Error.h"
#include "Common/Mathematics.h"

#include "Components/ModelComponent.h"

void SetSideVertices(std::vector<Vector3> positions, Vector3 normal, std::vector<Vertex>& shape_vertices, size_t starting_index)
{
    if(starting_index + positions.size() > shape_vertices.size())
    {
        CriticalError(ENGINE_ERROR, "Number Of Provided Positions + Starting Index Exceeds The Amount Of Vertices Of The Shape\n");
        return;
    }

    for(int i = 0; i < positions.size(); i++)
    {
        shape_vertices[starting_index + i] = Vertex(positions[i], normal, Color(0xff, 0xff, 0xff, 0xff), TextureCoord(0, 0, 0));
    }
}

/*//TODO: Give circle an angle by using normals
std::vector<Vertex> Circle(float radius, int triangles, Color color, std::vector<Vertex>& shape, size_t shape_index)
{
    std::vector<Vertex> circle = std::vector<Vertex>(triangles * 3);
    Vector3 center = Vector3(0, 0, 0);
    Vector3 first_point;
    Vector3 second_point;
    float radian = 0;

    int i = 0;
    while(i < triangles)
    {
        first_point.x = cos(radian) * radius;
        first_point.y = sin(radian) * radius;

        radian += (2 * M_PI) / triangles;
        second_point.x = cos(radian) * radius;
        second_point.y = sin(radian) * radius;

        Triangle(center, first_point, second_point, color, circle, i * 3);
        shape[shape_index] = Vertex(center, color);
        shape[shape_index + 1] = Vertex(first_point, color);
        shape[shape_index + 2] = Vertex(second_point, color);

        i++;
    }

    return circle;
}*/

Shared<CModel> PrismInvisible(float width, float height, float depth)
{
    std::vector<Vertex> vertices = std::vector<Vertex>(24);
    std::vector<ushort> indices = std::vector<ushort>(30); //24 Indices + 6 Primitive Restart Indices
    std::vector<size_t> face_offsets = std::vector<size_t>(6);

    const Vector3 origin = Vector3(-width / 2, -height / 2, -depth / 2);
    const Vector3 X = origin + Vector3(width, 0, 0);
    const Vector3 Y = origin + Vector3(0, height, 0);
    const Vector3 Z = origin + Vector3(0, 0, depth);
    const Vector3 XY = origin + Vector3(width, height, 0);
    const Vector3 XZ = origin + Vector3(width, 0, depth);
    const Vector3 YZ = origin + Vector3(0, height, depth);
    const Vector3 XYZ = origin + Vector3(width, height, depth);

    Vector3 x_normal = Vector3(1.0f, 0.0f, 0.0f);
    Vector3 y_normal = Vector3(0.0f, 1.0f, 0.0f);
    Vector3 z_normal = Vector3(0.0f, 0.0f, 1.0f);

    //Set Vertices
    SetSideVertices({X, XY, XZ, XYZ}, x_normal, vertices, 0); //Right
    SetSideVertices({Y, XY, YZ, XYZ}, y_normal, vertices, 4); //Top
    SetSideVertices({Z, XZ, YZ, XYZ}, z_normal, vertices, 8); //Front
    SetSideVertices({origin, Y, Z, YZ}, -x_normal, vertices, 12); //Left
    SetSideVertices({origin, X, Z, XZ}, -y_normal, vertices, 16); //Bottom
    SetSideVertices({origin, X, Y, XY}, -z_normal, vertices, 20); //Back

    //Set Indices
    int index = 0;
    int face_offset = 0;
    for(int i = 0; i < indices.size(); i++)
    {
        if((i + 1) % 5 == 0)
        {
            indices[i] = PRIMITIVE_RESTART;
            face_offsets[face_offset] = 5 * face_offset;
            face_offset++;

            continue;
        }

        indices[i] = index;
        index++;
    }

    Shared<CModel> prism = CreateShared<CModel>(vertices, indices, face_offsets);
    return prism;
}

Shared<CModel> PrismColored(float width, float height, float depth, Color front, Color back, Color left, Color right, Color top, Color bottom)
{
    Shared<CModel> prism = PrismInvisible(width, height, depth);
    prism->SetMultipleFaceColors({0, 1, 2, 3, 4, 5}, {right, top, front, left, bottom, back});

    return prism;
}
Shared<CModel> PrismTextured
(
    float width, float height, float depth,
    Shared<ModelTexture> front, Shared<ModelTexture> back,
    Shared<ModelTexture> left, Shared<ModelTexture> right,
    Shared<ModelTexture> top, Shared<ModelTexture> bottom
)
{
    Shared<CModel> prism = PrismInvisible(width, height, depth);

    TextureCoord bottom_left = TextureCoord(0.0f, 0.0f);
    TextureCoord bottom_right = TextureCoord(1.0f, 0.0f);
    TextureCoord top_left = TextureCoord(0.0f, 1.0f);
    TextureCoord top_right = TextureCoord(1.0f, 1.0f);

    prism->SetMultipleFaceTextureCoords
    (
        {0, 1, 2, 3, 4, 5},
        {
            {bottom_right, top_right, bottom_left, top_left},
            {bottom_left, bottom_right, top_left, top_right},
            {bottom_left, bottom_right, top_left, top_right},
            {bottom_left, top_left, bottom_right, top_right},
            {top_left, bottom_left, top_right, bottom_right},
            {bottom_right, bottom_left, top_right, top_left}

        }
    );

    prism->textures = {right, top, front, left, bottom, back};
    return prism;
}

Shared<CModel> CubeInvisible(float size)
{
    return PrismInvisible(size, size, size);
}

Shared<CModel> CubeColored(float size, Color front, Color back, Color left, Color right, Color top, Color bottom)
{
    return PrismColored(size, size, size, front, back, left, right, top, bottom);
}

Shared<CModel> CubeTextured
(
    float size,
    Shared<ModelTexture> front, Shared<ModelTexture> back,
    Shared<ModelTexture> left, Shared<ModelTexture> right,
    Shared<ModelTexture> top, Shared<ModelTexture> bottom
)
{
    return PrismTextured(size, size, size, front, back, left, right, top, bottom);
}

Shared<CModel> Pyramid4Invisible(float depth, float height, float width)
{
    std::vector<Vertex> vertices = std::vector<Vertex>(16);
    std::vector<ushort> indices = std::vector<ushort>(20); // 16 Indices + 4 Primitive Restart Indices
    std::vector<size_t> face_offsets = std::vector<size_t>(5);

    const Vector3 origin = Vector3(-width / 2, -height / 2, -depth / 2);
    const Vector3 X = origin + Vector3(width, 0, 0);
    const Vector3 Y = Vector3(0, height / 2, 0);
    const Vector3 Z = origin + Vector3(0, 0, depth);
    const Vector3 XZ = origin + Vector3(width, 0, depth);

    const Vector3 x_angled_normal = TriangleNormal(X, Y, XZ);
    const Vector3 z_angled_normal = TriangleNormal(Z, Y, XZ);
    const Vector3 neg_x_angled_normal = x_angled_normal * Vector3(-1.0f, 1.0f, 1.0f);
    const Vector3 neg_z_angled_normal = z_angled_normal * Vector3(1.0f, 1.0f, -1.0f);
    const Vector3 neg_y_normal = Vector3(0.0f, -1.0f, 0.0f);

    //Set Vertices
    SetSideVertices({X, Y, XZ}, x_angled_normal, vertices, 0);
    SetSideVertices({Z, Y, XZ}, z_angled_normal, vertices, 3);
    SetSideVertices({origin, Y, Z}, neg_x_angled_normal, vertices, 6); //Normal Is Flipped In X Direction
    SetSideVertices({origin, Y, X}, neg_z_angled_normal, vertices, 9); //Normal Is Flipped In Z Direction
    SetSideVertices({origin, X, Z, XZ}, neg_y_normal, vertices, 12);

    //Set Indices
    int index = 0;
    int face_offset = 0;
    for(int i = 0; i < indices.size(); i++)
    {
        if((i + 1) % 4 == 0)
        {
            indices[i] = PRIMITIVE_RESTART;
            face_offsets[face_offset] = 4 * face_offset;
            face_offset++;

            continue;
        }

        indices[i] = index;
        index++;
    }

    std::swap(indices[index], indices[index - 1]); //The Fourth Index Of Base Is At The End, Swap It With Primitive Restart

    Shared<CModel> pyramid = CreateShared<CModel>(vertices, indices, face_offsets);
    return pyramid;
}

Shared<CModel> Pyramid4Colored(float depth, float height, float width, Color front, Color back, Color left, Color right, Color bottom)
{
    Shared<CModel> pyramid = Pyramid4Invisible(depth, height, width);

    //Set Colors
    pyramid->SetMultipleFaceColors({0, 1, 2, 3, 4}, {right, front, left, back, bottom});

    return pyramid;
}

Shared<CModel> Pyramid4Textured
(
    float depth, float height, float width,
    Shared<ModelTexture> front, Shared<ModelTexture> back,
    Shared<ModelTexture> left, Shared<ModelTexture> right,
    Shared<ModelTexture> top, Shared<ModelTexture> bottom
)
{
    Shared<CModel> pyramid = Pyramid4Invisible(depth, height, width);

    const TextureCoord bottom_left = TextureCoord(0.0f, 0.0f);
    const TextureCoord bottom_right = TextureCoord(1.0f, 0.0f);
    const TextureCoord top_left = TextureCoord(0.0f, 1.0f);
    const TextureCoord top_right = TextureCoord(1.0f, 1.0f);
    const TextureCoord top_tex_coord = TextureCoord(0.5f, 0.5f);

    pyramid->SetMultipleFaceTextureCoords
    (
        {0, 1, 2, 3, 4},
        {
            {bottom_left, top_tex_coord, bottom_right}, //Right
            {bottom_left, top_tex_coord, bottom_right}, //Front
            {bottom_right, top_tex_coord, bottom_left}, //Left
            {bottom_left, top_tex_coord, bottom_right}, //Back
            {top_left, bottom_left, top_right, bottom_right} //Bottom
        }
    );

    pyramid->textures = {right, front, left, back, bottom};
    return pyramid;
}

/*Shared<CModel> Cylinder(float radius, float height, int triangles, Color color)
{
    std::vector<Vertex> vertices = std::vector<Vertex>(triangles * 24);
    Circle(radius, triangles, color, vertices, 0);
    Circle(radius, triangles, color, vertices, 24);

    int i = 0;
    while(i < triangles)
    {
        Triangle(vertices[i + 1].vector, vertices[i + 2].vector, vertices[i + 25].vector, color, vertices, i + 48);
        Triangle(vertices[i + 1].vector, vertices[i + 2].vector, vertices[i + 26].vector, color, vertices, i + 49);
        i++;
    }

    Shared<CModel> cylinder = CreateShared<CModel>(vertices);
    return cylinder;
}*/
