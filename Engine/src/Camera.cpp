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

    Camera::Camera(const vec3& initPos, const vec3& initRight, const vec3* target)
    {
        this->SetPosition(initPos);
        this->Right = initRight;

        if (target)
        {
            this->SetTargetLock(target);
        }
        else
        {
            this->UnlockTarget();
        }
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
        this->Position = pos;

        if (!this->IsTargetLock)
        {
            this->InternalTarget += this->Position;
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

    void Camera::SetTargetLock(const vec3* target)
    {
        if (!target)
            return;

        this->Target = target;
        this->IsTargetLock = true;

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
