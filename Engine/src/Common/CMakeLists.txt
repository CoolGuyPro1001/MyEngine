target_sources(
    ${ENGINE_NAME}
    PRIVATE

    Binary.h
    Color.h
    Error.h
    Console.h
    File.h
    Hex.h
    Log.h
    Mathematics.h
    Shapes.h
    TextureCoord.h
    Tree.h
    Vector2.h
    Vector3.h
    Vertex.h

    Binary.cpp
    Color.cpp
    Console.cpp
    File.cpp
    Hex.cpp
    Log.cpp
    Mathematics.cpp
    TextureCoord.cpp
    Vector2.cpp
    Vector3.cpp
    Vertex.cpp
)

add_subdirectory(Shapes)
