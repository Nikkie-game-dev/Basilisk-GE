#pragma once
#include <spdlog/spdlog.h>

#include "Export.h"

namespace basilisk
{
    class BASILISK_API Log
    {
    public:
        static std::shared_ptr<spdlog::logger>& Print();
        ~Log();

        Log(const Log& other) = delete; // copy constructor
        Log(Log&& other) noexcept = delete; // move constructor
        Log& operator=(const Log& other) = delete; // copy assignment
        Log& operator=(Log&& other) noexcept = delete; // move assignment

    private:
        Log();
        std::shared_ptr<spdlog::logger> Logger;
    };

} // basilisk
