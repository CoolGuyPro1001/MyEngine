if(ENABLE_RENDERING)
    target_sources(
        ${ENGINE_NAME}
        PRIVATE

        CameraComponent.h
        ModelComponent.h

        CameraComponent.cpp
        ModelComponent.cpp
    )

    if(ENABLE_COLLISION)
        target_sources(
            ${ENGINE_NAME}
            PRIVATE

            CollisionComponent.h
            CollisionComponent.cpp
        )
    endif()
endif()
