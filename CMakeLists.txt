cmake_minimum_required(VERSION 3.16)
project(trpg_engine_wannabe)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED SDL2)
find_package(SDL2 REQUIRED SDL2_gfx)
find_package(SDL2 REQUIRED SDL2_ttf)

include_directories(Widgets/src)
include_directories(Widgets/src/geom)
include_directories(Widgets/src/ui_widgets)

add_executable(trpg_engine_wannabe
        Widgets/src/geom/Dimension.cpp
        Widgets/src/geom/Dimension.h
        Widgets/src/geom/Position.cpp
        Widgets/src/geom/Position.h
        Widgets/src/ui_widgets/Button.cpp
        Widgets/src/ui_widgets/Button.h
        Widgets/src/ui_widgets/Container.cpp
        Widgets/src/ui_widgets/Container.h
        Widgets/src/ui_widgets/Text.cpp
        Widgets/src/ui_widgets/Text.h
        Widgets/src/Application.cpp
        Widgets/src/Application.h
        Widgets/src/Collision.cpp
        Widgets/src/Collision.h
        Widgets/src/Main.cpp
        Widgets/src/Renderer.h
        Widgets/src/SDL_FontCache/SDL_FontCache.c
        Widgets/src/SDL_FontCache/SDL_FontCache.h)

target_link_libraries(trpg_engine_wannabe
        PRIVATE SDL2
        PRIVATE SDL2_gfx
        PRIVATE SDL2_ttf
        )