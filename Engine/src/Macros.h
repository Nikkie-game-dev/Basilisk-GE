#pragma once
// ReSharper disable CppClangTidyModernizeMacroToEnum
//@formatter:off

#ifdef _WIN32
    #ifdef BASILISK_EXPORT
        #define BASILISK_API __declspec(dllexport)
        #define BASILISK_EXTERN
    #else
        #define BASILISK_API __declspec(dllimport)
        #define BASILISK_EXTERN extern
    #endif
#endif

#pragma region Common Data

    #define AMOUND_DIM 3

#pragma endregion

//@formatter:on