cmake_minimum_required(VERSION 3.21)
project(chakram_game)

add_executable(game
        main.cpp
        )

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

target_link_libraries(game
        PRIVATE glad::glad glfw glm::glm
)