cmake_minimum_required(VERSION 3.17)
project(SDL2Game)

set(CMAKE_CXX_STANDARD 17)

# Add SDL2 CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

# Set output path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_net REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

set(BIN_NAME MySDLGameDemo)

file(GLOB SRC src/*.cpp)

add_executable(${BIN_NAME} ${SRC})

target_include_directories(${BIN_NAME} PUBLIC src)
target_include_directories(${BIN_NAME} PUBLIC ${SDL2_INCLUDE_DIR})
target_link_libraries(${BIN_NAME} SDL2::Main SDL2::Net SDL2::Image SDL2::Mixer
        SDL2::TTF m)


file(COPY res DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})