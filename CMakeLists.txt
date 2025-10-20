cmake_minimum_required(VERSION 4.1.2)
project(ToyEngine LANGUAGES CXX C)

# Set C/C++ standard
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add your sources
add_executable(main
  Source/Private/main.cpp
  Source/Private/glad.c
)

# Include directories
target_include_directories(main
  PRIVATE
  Include
  Source/Public
)

# Link directories
target_link_directories(main
  PRIVATE
  Libs
)

# Link libraries
target_link_libraries(main
  PRIVATE
  glfw3.lib
  opengl32.lib
  gdi32.lib
  user32.lib
  shell32.lib
)
