#include "Camera.h"

namespace Graphics
{
    void Camera::MoveCameraForward(float dis)
    {
        position.x += glm::cos(orientation.y) * dis;
        position.z += glm::sin(orientation.y) * dis;
        position.y += glm::sin(orientation.p) * dis;

        looking_at.x += glm::cos(orientation.y) * dis;
        looking_at.z += glm::sin(orientation.y) * dis;
        looking_at.y += glm::sin(orientation.p) * dis;
    }

    void Camera::MoveCameraSideways(float dis)
    {
        constexpr float HALF = glm::pi<float>() / 2;
        
        position.x += glm::cos(orientation.y - HALF) * dis;
        position.z += glm::sin(orientation.y - HALF) * dis;

        looking_at.x += glm::cos(orientation.y - HALF) * dis;
        looking_at.z += glm::sin(orientation.y - HALF) * dis;
    }

    void Camera::MoveCameraUpwards(float dis)
    {
        position.y += dis;
        looking_at.y += dis;
    }


    void Camera::TurnCameraP(float deg)
    {
        AddToOrientation(orientation.p, deg, false);
        looking_at.y = glm::sin(orientation.p) * focal_distance + position.y;
        looking_at.x = glm::cos(orientation.y) * focal_distance + position.x;
        looking_at.z = glm::sin(orientation.y) * focal_distance + position.z;
    }

    void Camera::TurnCameraY(float deg)
    {
        AddToOrientation(orientation.y, deg, true);
        looking_at.x = glm::cos(orientation.y) * focal_distance + position.x;
        looking_at.z = glm::sin(orientation.y) * focal_distance + position.z;
    }

    void Camera::TurnCameraR(float deg)
    {
        AddToOrientation(orientation.r, deg, true);
        looking_at.x = glm::cos(orientation.z) * focal_distance + position.x;
        looking_at.y = glm::sin(orientation.z) * focal_distance + position.y;
    }
    
    void Camera::AddToOrientation(float& axis, float deg, bool full_circle)
    {
        axis += deg;
        constexpr float PI = glm::pi<float>();

        if(full_circle)
        {
            if(axis > PI)
            {
                axis = -PI + (axis - PI);
            }
            else if(axis < -PI)
            {
                axis = PI + (axis + PI);
            }
        }
        else
        {
            if(axis > PI / 2)
            {
                axis = PI / 2;
            }
            else if(axis < -PI / 2)
            {
                axis = -PI / 2;
            }    
        }  
    }

    void Camera::PrintCameraLocation()
    {
        std::cout << "At| X:" << position.x <<  " Y:" << position.y << " Z:" << position.z << "\n";
        std::cout << "Looking At| X:" << looking_at.x << " Y:" << looking_at.y << " Z:" << looking_at.z << "\n";
        std::cout << "Orientation| P:" << orientation.p << " Y:" << orientation.y << " R:" << orientation.r << "\n";
    }
}