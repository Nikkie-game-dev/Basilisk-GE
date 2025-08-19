#pragma once

#ifdef _WIN32
    #ifdef BASILISK_EXPORT
        #define BASILISK_API __declspec(dllexport)
    #else
        #define BASILISK_API __declspec(dllimport)
    #endif
#endif