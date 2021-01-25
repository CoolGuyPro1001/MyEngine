#include "Camera.h"
#include "Core/Log.h"

namespace Graphics
{
    Camera::Camera()
    {
        position = Vector3(0, 0, 0);
        looking_at = Vector3(0, 0, 10);
        focal_distance = 50;
        orientation = Vector3(0, 0, 0);
        velocity = Vector3(0, 0, 0);
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
        Engine::Log("At| X: %f Y: %f Z: %f\n", position.x, position.y, position.z);
        Engine::Log("Looking At| X: %f Y: %f Z: %f\n", looking_at.x, looking_at.y, looking_at.z);
        Engine::Log("Orientation| P: %f Y: %f R: %f\n",orientation.pitch, orientation.yaw, orientation.roll);
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