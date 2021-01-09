#ifndef CAMERA_H
#define CAMERA_H

#include "Events.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Common/Units.h"

namespace Graphics
{
    class Camera
    {
    public:
        Camera();
        
        void MoveCameraForward();
        void MoveCameraSideways();
        void MoveCameraUpwards();
        void PrintCameraLocation();

        void TurnCameraP(float deg);
        void TurnCameraY(float deg);
        void TurnCameraR(float deg);

        void Tick();

        void OnStickX(StickXEvent e);
        void OnStickY(StickYEvent e);
        void OnUpButtonPress();
        void OnUpButtonRelease();
        void OnDownButtonPress();
        void OnDownButtonRelease();

        Vector3 position;
        Vector3 looking_at;
        float focal_distance;
        Vector3 orientation;
        Vector3 velocity;

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