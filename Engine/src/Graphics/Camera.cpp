#include "Camera.h"

namespace Graphics
{
    Camera::Camera()
    {
        Vector3 position = Vector3(0, 0, 0);
        Vector3 looking_at = Vector3(0, 0, 10);
        float focal_distance = 50;
        Vector3 orientation = Vector3(0, 0, 0);
        Vector3 velocity = Vector3(0, 0, 0);
    }

    void Camera::MoveCameraForward()
    {
        position.x += velocity.x;
        position.z += velocity.y;
        position.y += velocity.z;

        looking_at.x += velocity.x;
        looking_at.z += velocity.y;
        looking_at.y += velocity.z;
    }

    void Camera::MoveCameraSideways()
    {    
        position.x += velocity.x;
        position.z += velocity.z;

        looking_at.x += velocity.x;
        looking_at.z += velocity.z;
    }

    void Camera::MoveCameraUpwards()
    {
        position.y += velocity.y;
        looking_at.y += velocity.y;
    }


    void Camera::TurnCameraP(float deg)
    {
        AddToOrientation(orientation.pitch, deg, false);
        looking_at.y = glm::sin(orientation.pitch) * focal_distance + position.y;
        looking_at.x = glm::cos(orientation.yaw) * focal_distance + position.x;
        looking_at.z = glm::sin(orientation.yaw) * focal_distance + position.z;
    }

    void Camera::TurnCameraY(float deg)
    {
        AddToOrientation(orientation.yaw, deg, true);
        looking_at.x = glm::cos(orientation.yaw) * focal_distance + position.x;
        looking_at.z = glm::sin(orientation.yaw) * focal_distance + position.z;
    }

    void Camera::TurnCameraR(float deg)
    {
        AddToOrientation(orientation.roll, deg, true);
        looking_at.x = glm::cos(orientation.roll) * focal_distance + position.x;
        looking_at.y = glm::sin(orientation.roll) * focal_distance + position.y;
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
        std::cout << "Orientation| P:" << orientation.pitch << " Y:" << orientation.yaw << " R:" << orientation.roll << "\n";
    }

    void Camera::Tick()
    {
        MoveCameraForward();
        MoveCameraSideways();
        MoveCameraUpwards();
    }

    void Camera::OnStickX(StickXEvent e)
    {
        float distance = e.value * 0.001;
        constexpr float HALF = glm::pi<float>() / 2;
        
        velocity.x += glm::cos(orientation.yaw - HALF) * distance;
        velocity.z += glm::sin(orientation.yaw - HALF) * distance;
    }

    void Camera::OnStickY(StickYEvent e)
    {
        float distance = e.value * 0.001;
        velocity.x = glm::cos(orientation.yaw) * distance;
        velocity.y = glm::sin(orientation.pitch) * distance;
        velocity.z = glm::sin(orientation.yaw) * distance;
    }

    void Camera::OnUpButtonPress()
    {
        velocity.y = 5;
    }

    void Camera::OnUpButtonRelease()
    {
        velocity.y = 0;
    }

    void Camera::OnDownButtonPress()
    {
        velocity.y = -5;
    }

    void Camera::OnDownButtonRelease()
    {
        velocity.y = 0;
    }
}