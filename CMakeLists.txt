cmake_minimum_required(VERSION 4.1)
project(ToyEngine)

# Set C/C++ standard
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(
  Include
)

# Link directories
link_directories(Libs)

# Add your sources
add_executable(main
  Source/Private/main.cpp
  Source/Private/glad.c
)

# Link libraries
target_link_libraries(main
  glfw3.lib
  opengl32.lib
  gdi32.lib
  user32.lib
  shell32.lib
)
