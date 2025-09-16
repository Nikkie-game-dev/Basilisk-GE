#pragma once

#ifdef _WIN32
    #ifdef BASILISK_EXPORT
        #define BASILISK_API __declspec(dllexport)
        #define BASILISK_EXTERN
    #else
        #define BASILISK_API __declspec(dllimport)
        #define BASILISK_EXTERN extern
    #endif
#endif