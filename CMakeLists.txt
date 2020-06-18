cmake_minimum_required(VERSION 3.16)
project(trpg_engine_wannabe)

set(CMAKE_CXX_STANDARD 14)
set(SDL_MOUSE_RELATIVE 0)
set(SDL_VIDEO_X11_DGAMOUSE 0)
set(SDL_VIDEO_X11_MOUSEACCEL "1/1/1")

find_package(SDL2 REQUIRED SDL2)
find_package(SDL2 REQUIRED SDL2_gfx)
find_package(SDL2 REQUIRED SDL2_ttf)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(Widgets/src)
include_directories(Widgets/src/geom)
include_directories(Widgets/src/ui_widgets)

file(COPY Widgets/src/shaders DESTINATION ${CMAKE_BINARY_DIR})

add_executable(trpg_engine_wannabe
        Widgets/src/geom/Dimension.cpp
        Widgets/src/geom/Dimension.h
        Widgets/src/geom/Position.cpp
        Widgets/src/geom/Position.h
        Widgets/src/ui_widgets/Button.cpp
        Widgets/src/ui_widgets/Button.h
        Widgets/src/ui_widgets/Container.cpp
        Widgets/src/ui_widgets/Container.h
        Widgets/src/Application.cpp
        Widgets/src/Application.h
        Widgets/src/Collision.cpp
        Widgets/src/Collision.h
        Widgets/src/Main.cpp
        Widgets/src/Renderer.h
        Widgets/src/Shader.cpp Widgets/src/Shader.h)

target_link_libraries(trpg_engine_wannabe
        PRIVATE SDL2
        PRIVATE SDL2_gfx
        PRIVATE SDL2_ttf
        ${OPENGL_LIBRARIES}
        PRIVATE GLEW
        )