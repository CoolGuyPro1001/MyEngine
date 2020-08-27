#ifndef CAMERA_H
#define CAMERA_H

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace Graphics
{
    class Camera
    {
    public:
        void MoveCameraForward(float dis);
        void MoveCameraSideways(float dis);
        void MoveCameraUpwards(float dis);
        void PrintCameraLocation();

        void TurnCameraP(float deg);
        void TurnCameraY(float deg);
        void TurnCameraR(float deg);

        glm::mat3 RotationMatrixX(float deg);
        glm::mat3 RotationMatrixY(float deg);
        glm::mat3 RotationMatrixZ(float deg);
        
        glm::vec3 position = glm::vec3(0, 0, 0);
        glm::vec4 looking_at = glm::vec4(10, 0, 0, 1);
        float focal_distance = 50;
        glm::vec3 orientation = glm::vec3(0, 0, 0);

        void Transform(glm::vec4& v, glm::mat4 m);
        void AddToOrientation(float& axis, float deg, bool doNegative);
    private:
        //constexpr glm::vec3 camera_front = glm::vec3(0, 0, 1);
        //constexpr glm::vec3 camera_back = glm::vec3(0, 0, -1);
        //constexpr glm::vec3 camera_right = glm::vec3(1, 0, 0);
        //constexpr glm::vec3 camera_left = glm::vec3(-1, 0, 0);
        //constexpr glm::vec3 camera_up = glm::vec3(0, 1, 0);
        //constexpr glm::vec3 camera_down = glm::vec3(0, -1, 0);

        
        //glm::vec3 camera_orientation = camera_front;
    };
}
#endif