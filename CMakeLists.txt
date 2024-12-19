# Angiv vcpkg toolchain-fil
set(CMAKE_TOOLCHAIN_FILE "C:/Users/Adam_/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

cmake_minimum_required(VERSION 3.12)
project(ION-Launcher)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add ImGui core files
set(IMGUI_SRC
    include/imgui/imgui.cpp
    include/imgui/imgui_draw.cpp
    include/imgui/imgui_tables.cpp
    include/imgui/imgui_widgets.cpp
)

# Add ImGui backend files
set(IMGUI_BACKENDS
    backends/imgui_impl_glfw.cpp
    backends/imgui_impl_opengl3.cpp
)

# Add executable
add_executable(${PROJECT_NAME}
    src/main.cpp
    ${IMGUI_SRC}
    ${IMGUI_BACKENDS}
)

# Target include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include/imgui
    ${CMAKE_SOURCE_DIR}/backends
    ${CMAKE_SOURCE_DIR}/headers
)

# Find OpenGL and GLFW3
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED CONFIG)

# Link libraries
target_link_libraries(${PROJECT_NAME} 
    OpenGL::GL 
    glfw
)

# Platform-specific settings
if (WIN32)
    target_link_libraries(${PROJECT_NAME} OpenGL::GL glfw opengl32)
elseif (APPLE)
    find_library(COCOA_LIBRARY Cocoa REQUIRED)
    find_library(IOKIT_LIBRARY IOKit REQUIRED)
    find_library(COREVIDEO_LIBRARY CoreVideo REQUIRED)
    target_link_libraries(${PROJECT_NAME}
        OpenGL::GL
        glfw
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
        ${COREVIDEO_LIBRARY}
    )
elseif (UNIX)
    target_link_libraries(${PROJECT_NAME} OpenGL::GL glfw dl)
endif()
