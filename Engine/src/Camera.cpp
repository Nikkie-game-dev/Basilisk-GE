#include "Camera.h"

#include <memory>

#include "Log.h"

namespace basilisk
{
    Camera::Camera(const vec3& initPos, const vec3* target, const float initYaw)
    {
        this->SetPosition(initPos);
        this->SetYaw(initYaw);

        if (target)
        {
            this->SetTargetLock(target);
        }
        else
        {
            this->UnlockTarget();
        }
    }


    Camera::Camera(const vec3& initPos, const vec3& target, float initYaw)
    {
        this->SetPosition(initPos);
        this->SetYaw(initYaw);

        this->InternalTarget = target;
    }


    void Camera::SetYaw(const float yaw)
    {
        if (this->IsTargetLock)
        {
            Log::Get()->warn("Target lock is set! Cannot change yaw!");
            return;
        }

        this->Yaw = yaw;
        YawPitchToTarget();
    }


    void Camera::SetPitch(const float pitch)
    {
        if (this->IsTargetLock)
        {
            Log::Get()->warn("Target lock is set! Cannot change pitch!");
            return;
        }

        this->Pitch = pitch;
        YawPitchToTarget();
    }

    void Camera::SetRoll(float roll)
    {
        //todo
    }

    void Camera::SetPosition(const vec3& pos)
    {
        if (!this->IsPositionLock)
        {
            this->Position = pos;
        }
        else
        {
            Log::Get()->warn("Position is locked!.");
        }
    }

    float Camera::GetYaw() const
    {
        return this->Yaw;
    }

    float Camera::GetPitch() const
    {
        return this->Pitch;

    }

    float Camera::GetRoll() const
    {
        return this->Roll;

    }

    vec3 Camera::GetUp() const
    {
        constexpr vec3 worldUp = {0,1,0};
        const auto dir = normalize((this->Target ? *this->Target : this->InternalTarget) - this->Position);
        const auto right = cross(worldUp, dir);
        return cross(dir, right);
    }

    vec3 Camera::GetPosition() const
    {
        return this->Position;
    }

    vec3 Camera::GetTarget() const
    {
        return *this->Target;
    }

    bool Camera::IsTargetExternallyProvided() const
    {
        return this->IsTargetLock;
    }

    void Camera::UnlockTarget()
    {
        if (this->IsTargetLock)
        {
            //copy last target position and point Target to internal target
            this->InternalTarget = *this->Target;
            this->Target = &this->InternalTarget;
            this->IsTargetLock = false;
        }
    }
    
    void Camera::UnlockPosition()
    {
        if (this->IsPositionLock)
        {
            this->Position = *this->PositionTarget;
            this->PositionTarget = nullptr;
            this->IsPositionLock = false;
        }
    }

    void Camera::SetTargetLock(const vec3* target)
    {
        if (!target)
            return;

        this->Target = target;
        this->IsTargetLock = true;

    }
    
    void Camera::SetPositionLock(const vec3* target)
    {
        if (!target)
            return;

        this->PositionTarget = target;
        this->IsPositionLock = true;
    }

    void Camera::Update()
    {
        if (this->IsTargetLock)
        {
            this->TargetToYawPitch();
        }
        else
        {
            this->YawPitchToTarget();
        }
        
        if (this->IsPositionLock)
        {
            this->Position = *this->PositionTarget;
        }
    }

    void Camera::YawPitchToTarget()
    {
        const float pitchRad = radians(this->Pitch);
        const float yawRad = radians(this->Yaw);

        const float cosPitch = cos(pitchRad);

        this->InternalTarget.x = cos(yawRad) * cosPitch;
        this->InternalTarget.y = sin(pitchRad);
        this->InternalTarget.z = sin(yawRad) * cosPitch;
    }

    void Camera::TargetToYawPitch()
    {
        this->Pitch = asin(this->Target->y);
        this->Yaw = acos(this->Target->x / cos(this->Pitch));
    }
}
