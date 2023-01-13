project(fileDialog)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(fileDialog main.cpp)
target_compile_definitions(fileDialog PUBLIC WIN32)