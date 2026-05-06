#pragma once

#include <glm/glm.hpp>

#include "Macros.h"

namespace basilisk
{
    using namespace glm;

    class BASILISK_API Camera final
    {
    public:
        explicit Camera(const vec3& initPos, const vec3* target = nullptr, float initYaw = 0);
        explicit Camera(const vec3& initPos, const vec3& target, float initYaw = 0);


        void SetYaw(float yaw);
        void SetPitch(float pitch);
        void SetRoll(float roll);

        void SetPosition(const vec3& pos);

        [[nodiscard]] float GetYaw() const;
        [[nodiscard]] float GetPitch() const;
        [[nodiscard]] float GetRoll() const;

        [[nodiscard]] vec3 GetUp() const;
        [[nodiscard]] vec3 GetPosition() const;
        [[nodiscard]] vec3 GetTarget() const;
        
        [[nodiscard]] bool IsTargetExternallyProvided() const;
        
        void UnlockTarget();

        void SetTargetLock(const vec3* target);
        
        void Update();

    private:
        
        void YawPitchToTarget();
        void TargetToYawPitch();
        
        vec3 Position;
        vec3 InternalTarget;
        const vec3* Target;

        float Yaw;
        float Pitch;
        float Roll;

        bool IsTargetLock = false;
        
        
    };
} // basilisk 
