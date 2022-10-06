target_sources(
    ${ENGINE_NAME}
    PRIVATE

    Color.h
    Error.h
    Console.h
    Log.h
    Mathematics.h
    Matrix.h
    Shapes.h
    TextureCoord.h
    Tree.h
    Vector2.h
    Vector3.h
    Vertex.h

    Color.cpp
    Console.cpp
    Log.cpp
    Mathematics.cpp
    TextureCoord.cpp
    Vector2.cpp
    Vector3.cpp
    Vertex.cpp
)

add_subdirectory(Shapes)
