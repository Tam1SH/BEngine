# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Declares and names the project.

project("tbb_build")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

set(PROJECT_PATH "C:/.BEbraEngine")
set(LIB_PATH "${PROJECT_PATH}/platform/libs/debug/android")
set(INCLUDE_PATH "${PROJECT_PATH}/Include")

FILE(GLOB source_ ${PROJECT_PATH}/src/*.cpp)
FILE(GLOB headers_ ${PROJECT_PATH}/src/*.hpp ${PROJECT_PATH}/src/*.h )

set(SOURCE ${source_} )
add_library(main SHARED ${SOURCE} ${headers_})

target_include_directories(main PRIVATE
        ${INCLUDE_PATH}
        ${INCLUDE_PATH}/SDL
        ${INCLUDE_PATH}/glm
        ${INCLUDE_PATH}/Physics
        ${INCLUDE_PATH}/oneapi
        ${INCLUDE_PATH}/oneapi/tbb
        ${INCLUDE_PATH}/stb-master
        C:/VulkanSDK/1.2.170.0/Include/vulkan
        )


add_library(LIB_SDL SHARED IMPORTED)
add_library(LIB_SDL_API SHARED IMPORTED)
add_library(LIBC SHARED IMPORTED)
add_library(OMP SHARED IMPORTED)
add_library(BulletCollision SHARED IMPORTED)
add_library(BulletDynamics SHARED IMPORTED)
add_library(LinearMath SHARED IMPORTED)
add_library(libTBB SHARED IMPORTED)
add_library(libTBB_MALLOC SHARED IMPORTED)


set_property(TARGET OMP PROPERTY IMPORTED_LOCATION "${LIB_PATH}/${ANDROID_ABI}/libomp.so")
set_property(TARGET LIB_SDL PROPERTY IMPORTED_LOCATION "${LIB_PATH}/${ANDROID_ABI}/libSDL2.so")
set_property(TARGET LIBC PROPERTY IMPORTED_LOCATION "${LIB_PATH}/${ANDROID_ABI}/libc++_shared.so")
set_property(TARGET LIB_SDL_API PROPERTY IMPORTED_LOCATION "${LIB_PATH}/${ANDROID_ABI}/libhidapi.so")
set_property(TARGET BulletCollision PROPERTY IMPORTED_LOCATION "${LIB_PATH}/${ANDROID_ABI}/libBulletCollision.so")
set_property(TARGET BulletDynamics PROPERTY IMPORTED_LOCATION "${LIB_PATH}/${ANDROID_ABI}/libBulletDynamics.so")
set_property(TARGET LinearMath PROPERTY IMPORTED_LOCATION "${LIB_PATH}/${ANDROID_ABI}/libLinearMath.so")
set_property(TARGET libTBB PROPERTY IMPORTED_LOCATION "${LIB_PATH}/${ANDROID_ABI}/libtbb_debug.so")
set_property(TARGET libTBB_MALLOC PROPERTY IMPORTED_LOCATION "${LIB_PATH}/${ANDROID_ABI}/libtbbmalloc_debug.so")

find_library(vulkan vulkan-lib)

target_link_libraries(main
        LIB_SDL
        LIB_SDL_API
        LIBC
        vulkan
        OMP
        BulletCollision BulletDynamics LinearMath
        libTBB libTBB_MALLOC
       # ${SOURCE}
        )
#add_subdirectory(${CMAKE_SOURCE_DIR}/oneTBB-master)

# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.
#link_directories(C:/Users/ignat/AndroidStudioProjects/TBB_BUILD/app/src/main/jniLibs/arm64-v8a)


# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

