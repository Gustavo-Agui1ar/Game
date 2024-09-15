cmake_minimum_required(VERSION 3.5)

project(Game
    LANGUAGES CXX
    VERSION 1.0
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(DCMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES OFF)

# Find the SFML library
find_package(SFML 2.6 COMPONENTS system window graphics REQUIRED)

# Define the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}../../)

# Define compilation flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Add include directories
include_directories(include)

# Create a list of all source and header files
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/**/*.cpp")
file(GLOB_RECURSE HEADERS "includes/*.h" "includes/**/*.h")

# Create the target executable and link with SFML libraries
add_executable(${PROJECT_NAME}  ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

# Add include and src directories as include directories for the targets
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/includes" "${CMAKE_SOURCE_DIR}/src")

# Link the SFML library to every file, directory, and subdirectory in the project
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-network sfml-audio) 