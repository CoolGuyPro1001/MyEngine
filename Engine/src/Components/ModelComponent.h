#ifndef MODELCOMPONENT_H
#define MODELCOMPONENT_H

#include "Component.h"

#include "Common/Vertex.h"

struct Level;
struct ModelTexture;

struct CModel : public Component, public std::enable_shared_from_this<CModel>
{
    CModel();
    CModel(Shared<CModel> other);

    CModel(std::vector<Vertex> vertices, std::vector<ushort> indices, std::vector<size_t> face_offsets);
    CModel(std::vector<Vertex> vertices, std::vector<ushort> indices, std::vector<size_t> face_offsets, std::vector<Shared<ModelTexture>> textures);
    CModel(std::string file_path, std::vector<Shared<ModelTexture>> textures);
    CModel(const CModel& m);

    void AttachToLevel(Level& lvl);

    //Face Functions

    /**
    * \brief Returns The Polygon Face Color
    * \param face_index The Index Of The Polygon Face
    * \return Polygon Face Color
    */
    Color GetFaceColor(uint face_index);

    /**
    * \brief Returns The Texture Coordinates Of The Polygon Face
    * \param face_index The Index Of The Polygon Face
    * \return TextureCoords Of Polygon Face Vertices
    */
    std::vector<TextureCoord> GetFaceTextureCoordinates(uint face_index);

    /**
    * \brief Sets Polygon Face To A New Color
    * \param face_index The Index Of The Polygon Face
    * \param color Polygon Face Coloro
    */
    void SetFaceColor(uint face_index, Color color);

    /**
    * \brief Sets Multiple Polygon Faces To A New Color
    * \param face_indices List Of Indices Of The Polygon Faces
    * \param color Shared Color For Polygon Faces
    */
    void SetMultipleFaceColor(std::vector<uint> face_indices, Color color);

    /**
    * \brief Sets Multiple Polygon Faces To A Multiple Different Corresponding Colors
    * \param face_indices List Of Indices Of The Polygon Faces
    * \param colors List Of Polygon Face Colors
    */
    void SetMultipleFaceColors(std::vector<uint> face_indices, std::vector<Color> colors);

    /**
    * \brief Sets Multiple Polygon Faces To A Multiple Different Corresponding Colors
    * \param face_indices List Of Indices Of The Polygon Faces
    * \param colors List Of Polygon Face Colors
    */
    void SetFaceTextureCoords(uint face_index, std::vector<TextureCoord> tex_coords);

    /**
    * \brief Sets Multiple Polygon Faces To A Multiple Different Corresponding Colors
    * \param face_indices List Of Indices Of The Polygon Faces
    * \param colors List Of Polygon Face Colors
    */
    void SetMultipleFaceTextureCoords(std::vector<uint> face_indices, std::vector<std::vector<TextureCoord>> tex_coords_collection);


    std::vector<Vertex> vertices;
    std::vector<size_t> face_offsets; //The Offsets Of Each Face (Indices + Primitive Restart)
    std::vector<ushort> indices;

    std::vector<Shared<ModelTexture>> textures;
};
#endif
