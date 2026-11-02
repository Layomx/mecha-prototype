cmake_minimum_required(VERSION 3.25)

project(
    mecha_prototype
    VERSION 0.1.0
    DESCRIPTION "Low-poly mecha game prototype"
    LANGUAGES CXX
)

option(MECHA_BUILD_TESTS "Build the test suite" ON)
option(MECHA_ENABLE_WARNINGS "Enable strict compiler warnings" ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(mecha_warnings INTERFACE)

if(MECHA_ENABLE_WARNINGS)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        target_compile_options(
            mecha_warnings
            INTERFACE
                -Wall
                -Wextra
                -Wpedantic
                -Wconversion
                -Wsign-conversion
                -Wshadow
        )
    elseif(MSVC)
        target_compile_options(mecha_warnings INTERFACE /W4 /permissive-)
    endif()
endif()

add_library(mecha_core STATIC
    src/core/application.cpp
)

target_compile_features(mecha_core PUBLIC cxx_std_23)
target_include_directories(
    mecha_core
    PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
)
target_link_libraries(mecha_core PRIVATE mecha_warnings)

add_executable(mecha_prototype
    src/main.cpp
)
target_link_libraries(mecha_prototype PRIVATE mecha_core mecha_warnings)

include(CTest)
if(MECHA_BUILD_TESTS)
    add_subdirectory(tests)
endif()
