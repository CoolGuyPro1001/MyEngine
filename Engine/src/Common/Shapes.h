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

/**
 * Square() And Rectangle() Are Used For GUI Rendering
 * The Order Of Vertices For Square() And Rectangle() With Multiple Colors/Texture Coordinates As Parameters Are:
 * Bottom Left, Bottom Right, Upper Right, Bottom Left, Upper Left, Upper Right.
 * To Set Texture Coords Of The Bottom Of An Object, Treat The Object Like A Coin
 * For Examples Of Creating 2D Shapes, See \ref Shapes2DExamples
 * For General Information About The GUI, See \ref GUI
 */

/**
 * \brief Creates A Square With A Single Given Color
 * \param z_depth Z-Depth
 * \param color Color
 * \return The Square's Vertices
 */
std::array<Vertex, 6> Square(float size, float z_depth, Color color);

/**
 * \brief Creates A Square Where Each Vertex Has A Different Color Value
 * \param z_depth Z-Depth
 * \param colors The Colors Of Each Side
 * \return The Square's Vertices
 */
std::array<Vertex, 6> Square(float size, float z_depth, std::array<Color, 6> colors);

/**
 * \brief Creates A Square Where Each Vertex Has A Different Texture Coordinate
 * \param z_depth Z-Depth
 * \param tex_coords An Array Of Texture Cooordinates
 * \return The Square's Vertices
 */
std::array<Vertex, 6> Square(float size, float z_depth, std::array<TextureCoord, 6> tex_coords);

/**
 * \brief Creates A Square Where Each Vertex Has A Different Texture Coordinate, Mixed With A Color
 * \param z_depth Z-Depth
 * \param color Blending Color
 * \param tex_coords An Array Of Texture Coordinates
 * \return The Square's Vertices
 */
std::array<Vertex, 6> Square(float size, float z_depth, Color color, std::array<TextureCoord, 6> tex_coords);

/**
 * \brief Creates A Rectangle With A Single Given Color
 * \param z_depth Z-Depth
 * \param color Color
 * \return The Rectangle's Vertices
 */
std::array<Vertex, 6> Rectangle(float width, float height, float z_depth, Color color);

/**
 * \brief Creates A Square Where Each Vertex Has A Different Color Value
 * \param z_depth Z-Depth
 * \param colors The Colors Of Each Side
 * \return The Square's Vertices
 */
std::array<Vertex, 6> Rectangle(float width, float height, float z_depth, std::array<Color, 6> colors);

/**
 * \brief Creates A Rectangle Where Each Side Has A Unique Texture Coordinate
 * \param z_depth Z-Depth. See \ref Z-Depth
 * \param tex_coords Texture Coordinate
 * \return The Rectangle's Vertices
 */
std::array<Vertex, 6> Rectangle(float width, float height, float z_depth, std::array<TextureCoord, 6> tex_coords);

/**
 * \brief Creates A Rectangle Where Each Vertex Has A Different Texture Coordinate, Mixed With A Color
 * \param z_depth Z-Depth
 * \param color Blending Color
 * \param tex_coords An Array Of Texture Coordinates
 * \return The Rectangle's Vertices
 */
std::array<Vertex, 6> Rectangle(float width, float height, float z_depth, Color color, std::array<TextureCoord, 6> tex_coords);

std::vector<Vertex> Circle(float radius, int triangles, Color color, std::vector<Vertex>& shape, size_t shape_index);

/*
 * 3D Shapes
 * ===============================================================================================================
 */

void SetSideVertices(std::vector<Vector3> positions, Vector3 normal, Color color, std::vector<Vertex>& shape_vertices, size_t starting_index);
void SetSideVertices(std::vector<Vector3> positions, Vector3 normal, std::vector<TextureCoord> tex_coords, std::vector<Vertex>& shape_vertices, size_t starting_index);

/**
 * \brief Creates A Cube With A Different Color For Each Side
 * \param size Cube Size
 * \param front Front Side Color
 * \param back Back Side Color
 * \param left Left Side Color
 * \param right Right Side Color
 * \param top Top Side Color
 * \param bottom Bottom Side Color
 * \return A CModel Of The Cube
 */
Shared<CModel> Cube(float size, Color front, Color back, Color left, Color right, Color top, Color bottom);

/**
 * \brief Creates A Cube With A Different Texture For Each Side. The Texture Coordinates Are Automatically Calculated
 * \param size Cube Size
 * \param front Front Side Texture
 * \param back Back Side Texture
 * \param left Left Side Texture
 * \param right Right Side Texture
 * \param top Top Side Texture
 * \param bottom Bottom Side Texture
 * \return A CModel Of The Cube
 */
Shared<CModel> PrismInvisible(float width, float height, float depth);
Shared<CModel> PrismColored(float width, float height, float depth, Color front, Color back, Color left, Color right, Color top, Color bottom);
Shared<CModel> PrismTextured
(
    float width, float height, float depth,
    Shared<ModelTexture> front, Shared<ModelTexture> back,
    Shared<ModelTexture> left, Shared<ModelTexture> right,
    Shared<ModelTexture> top, Shared<ModelTexture> bottom
);

Shared<CModel> CubeInvisible(float size);
Shared<CModel> CubeColored(float size, Color front, Color back, Color left, Color right, Color top, Color bottom);
Shared<CModel> CubeTextured
(
    float size,
    Shared<ModelTexture> front, Shared<ModelTexture> back,
    Shared<ModelTexture> left, Shared<ModelTexture> right,
    Shared<ModelTexture> top, Shared<ModelTexture> bottom
);

Shared<CModel> Pyramid4Invisible(float depth, float height, float width);
Shared<CModel> Pyramid4Colored(float depth, float height, float width, Color front, Color back, Color left, Color right, Color bottom);
Shared<CModel> Pyramid4Textured
(
    float depth, float height, float width,
    Shared<ModelTexture> front, Shared<ModelTexture> back,
    Shared<ModelTexture> left, Shared<ModelTexture> right,
    Shared<ModelTexture> top, Shared<ModelTexture> bottom
);
//Shared<CModel> Cylinder(float radius, float height, int triangles, Color color);
#endif
