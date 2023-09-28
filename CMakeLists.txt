cmake_minimum_required(VERSION 3.20)
project(football)

set(CMAKE_CXX_STANDARD 20)

# Пытаемся найти предустановленный SFML
find_package(SFML COMPONENTS graphics)

if (SFML_FOUND)
    message(STATUS "The SFML installed in the system will be used")
else ()
    # Если SFML не найден - выкачиваем и собираем из исходников
    message(STATUS "Get SFML from the source code")
    include(FetchContent)
    FetchContent_Declare(SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 2.6.0)
    set(SFML_BUILD_AUDIO ON CACHE BOOL "" FORCE)
    set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
    # Обход потенциальных проблем при сборке sfml-graphics
    # (stb_image.h: 'argument': conversion from 'int' to 'short')
    set(WARNINGS_AS_ERRORS FALSE CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(SFML)
endif ()

add_executable(football
        main.cpp
        World.cpp
        Ball.cpp
        Physics.cpp
        Color.cpp
        Painter.cpp
        engine/Application.cpp
        engine/View.cpp
        engine/PainterImpl.cpp
        Dust.cpp Dust.h)

target_link_libraries(football PRIVATE sfml-graphics)

target_compile_options(football PRIVATE
        -Wall -Wextra -Wpedantic
        )
