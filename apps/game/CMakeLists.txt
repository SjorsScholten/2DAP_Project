cmake_minimum_required(VERSION 3.20)
project(chakram_game)

add_executable(game
        main.cpp

        ${CMAKE_SOURCE_DIR}/src/Shader.cpp
        ${CMAKE_SOURCE_DIR}/src/Texture.cpp
        ${CMAKE_SOURCE_DIR}/src/SpriteRenderer.cpp
        ${CMAKE_SOURCE_DIR}/src/ResourceManager.cpp
        )

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_path(STB_INCLUDE_DIRS "stb.h")

target_link_libraries(game
        PRIVATE glad::glad glfw glm::glm
)

target_include_directories(game
        PRIVATE ${STB_INCLUDE_DIRS}
)