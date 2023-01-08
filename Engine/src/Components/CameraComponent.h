#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include "Component.h"
#include "Common/Vector3.h"

struct Actor;
struct Level;

struct EAnalogInput;
struct EButtonInput;

/**
 * The Power Of Sight
 *
 * Velocity Is Measured In Units/Frame
 * Velocity Is Converted To Units/Frame Every Tick
 * Throttle is the maximum (positive) and minimum velocity (negative)
 * See Common/Vector.h For More Details On Coordinates And Rotation
 *
 * AttachRod() Will Attach An Imaginary Rod To An Actor
 * The Camera's Position Will Be Based On The Rod's Angle
 * Toggle [rod_lock] To Lock The Camera's Angle Towards The Actor's Position
 * Toggle [free_cam] To Free The Camera Even When Connected To Actor
 *
 * [zoom_velocity] Affects [focal_distance]
 * [view_velocity] Affects [fov]
 */


struct CCamera : public Component, public std::enable_shared_from_this<CCamera>
{
public:
    CCamera(float focal_distance, bool enable_logging, int log_delay);
    CCamera(const CCamera& c);

    void AttachToLevel(Level& lvl);

    /**
    * \brief Moves The Camera Directly Towards Where It's Looking At
    * \param e A Pointer To An Analog Event
    */
    void MoveDirectly(EAnalogInput* e);

    /**
    * \brief Moves The Camera Sideways Relative To Where It's Looking At
    * \param e A Pointer To An Analog Event
    */
    void MoveSideways(EAnalogInput* e);

    /**
    * \brief Moves The Camera Vertical Relative To Where It's Looking At
    * \param e A Pointer To An Analog Event.
    */
    void MoveVertical(EAnalogInput* e);


    void MoveUpwards(EButtonInput* e);
    void MoveDownwards(EButtonInput* e);
    void MoveRight(EButtonInput* e);
    void MoveLeft(EButtonInput* e);
    void MoveDown(EButtonInput* e);
    void MoveForwards(EButtonInput* e);
    void MoveBackwards(EButtonInput* e);

    void Pitch(EAnalogInput* e);
    void PitchUp(EButtonInput* e);
    void PitchDown(EButtonInput* e);
    void Yaw(EAnalogInput* e);
    void YawRight(EButtonInput* e);
    void YawLeft(EButtonInput* e);
    void Roll(EAnalogInput* e);
    void RollRight(EButtonInput* e);
    void RollLeft(EButtonInput* e);

    void Zoom(EAnalogInput* e);
    void ZoomIn(EButtonInput* e);
    void ZoomOut(EButtonInput* e);
    void View(EAnalogInput* e);

    void PrintInformation();

    void Tick();

    void AttachRod(Shared<Actor> actor, float length, Vector3 rotation, bool lock_on_actor);
    void RodPitch(EAnalogInput* e);
    void RodPitchUp(EButtonInput* e);
    void RodPitchDown(EButtonInput* e);
    void RodYaw(EAnalogInput* e);
    void RodYawRight(EButtonInput* e);
    void RodYawLeft(EButtonInput* e);
    void RodRoll(EAnalogInput* e);
    void RodRollRight(EButtonInput* e);
    void RodRollLeft(EButtonInput* e);

    void RodDistance(EAnalogInput*);
    void RodDistanceIn(EButtonInput* e);
    void RodDistanceOut(EButtonInput* e);

    void ToggleFreeCam();

    Vector3 position;
    Vector3 rotation;
    Vector3 position_velocity;
    Vector3 relative_position_velocity;

    Vector3 rotation_velocity;
    Vector3 rod_rotation;
    Vector3 rod_rotation_velocity;

    Vector3 up;
    Vector3 looking_at;

    float zoom_velocity;
    float view_velocity;
    float rod_length_velocity;

    float forward_throttle;
    float sideways_throttle;
    float vertical_throttle;

    float pitch_throttle;
    float yaw_throttle;
    float roll_throttle;

    float zoom_throttle;
    float view_throttle;

    Shared<Actor> attached_actor;
    bool free_cam;

    float rod_pitch_throttle;
    float rod_yaw_throttle;
    float rod_roll_throttle;
    float rod_length_throttle;
    bool rod_lock;

    float focal_distance;
    float rod_length;

    float fov;

private:
    int m_log_delay;
    int m_log_cooldown;
    bool m_log_on_tick;

    void AddToRotation(float& axis, float deg, bool doNegative);
};
#endif
