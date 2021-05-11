#ifndef CAMERA_H
#define CAMERA_H

#include "Events.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Common/Units.h"
#include "Actor.h"

namespace Graphics
{
    class Camera
    {
    public:
        Camera(float focal_distance, bool enable_logging, int log_delay);
        
        void MoveDirectly(StickYEvent e);
        void MoveSideways(StickXEvent e);
        void MoveVertical(StickYEvent e);
        void MoveUpwards(ButtonEvent e);
        void MoveDownwards(ButtonEvent e);
        void MoveRight(ButtonEvent e);
        void MoveLeft(ButtonEvent e);
        void MoveDown(ButtonEvent e);
        void MoveForwards(ButtonEvent e);
        void MoveBackwards(ButtonEvent e);

        void Pitch(StickYEvent e);
        void PitchUp(ButtonEvent e);
        void PitchDown(ButtonEvent e);
        void Yaw(StickXEvent e);
        void YawRight(ButtonEvent e);
        void YawLeft(ButtonEvent e);
        void Roll(StickXEvent e);
        void RollRight(ButtonEvent e);
        void RollLeft(ButtonEvent e);

        void PrintLocation();

        void Tick();

        void AttachRod(Shared<Actor> actor, float length, Vector3 rotation, bool lock_on_actor);
        void RodPitch(StickYEvent e);
        void RodPitchUp(ButtonEvent e);
        void RodPitchDown(ButtonEvent e);
        void RodYaw(StickXEvent e);
        void RodYawRight(ButtonEvent e);
        void RodYawLeft(ButtonEvent e);
        void RodRoll(StickXEvent e);
        void RodRollRight(ButtonEvent e);
        void RodRollLeft(ButtonEvent e);

        Vector3 position;
        Vector3 rotation;
        Vector3 position_velocity;
        Vector3 relative_position_velocity;
        Vector3 up;
        Vector3 rotation_velocity;
        Vector3 rod_rotation;
        Vector3 rod_rotation_velocity;
        Vector3 looking_at;

        float forward_throttle;
        float sideways_throttle;
        float vertical_throttle;

        float pitch_throttle;
        float yaw_throttle;
        float roll_throttle;

        Shared<Actor> attached_actor;

        float rod_pitch_throttle;
        float rod_yaw_throttle;
        float rod_roll_throttle;
        bool rod_lock;

        int log_delay;
        bool log_on_tick;

        float fov;

    private:

        float focal_distance;
        float rod_length;

        void AddToOrientation(float& axis, float deg, bool doNegative);
    };
}
#endif