# =======================================================================================
#
# ---------------------------------------------------------------------------------------
#
# =======================================================================================
cmake_minimum_required(VERSION 3.15...3.16)

#
## vcpkg
set(CMAKE_TOOLCHAIN_FILE
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/vcpkg/scripts/buildsystems/vcpkg.cmake
    CACHE STRING "vcpkg toolchain file"
)

project(vmix_todoapp_proj
    VERSION 0.1.0
    LANGUAGES CXX
)

#
## Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "c:/Qt/5.15.2/msvc2019_64" CACHE PATH "Qt dir")

find_package(Qt5 COMPONENTS Widgets REQUIRED)

enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)

option(BUILD_SHARED_LIBS    "Build shared libs" ON)
option(BUILD_TESTING        "Build tests"       ON)

add_executable(vmix_todoapp)

set_target_properties(vmix_todoapp PROPERTIES
    OUTPUT_NAME "todoapp"
)

target_compile_features(vmix_todoapp
    PRIVATE cxx_std_17
)

target_include_directories(vmix_todoapp
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

target_sources(vmix_todoapp
    PRIVATE
        src/main.cpp
)

target_link_libraries(vmix_todoapp Qt5::Widgets)

#
## taskio
add_subdirectory(libs/vmix-taskio)

target_link_libraries(vmix_todoapp vmix::taskio)
