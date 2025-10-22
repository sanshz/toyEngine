cmake_minimum_required(VERSION 3.10.3)
project(ToyEngine LANGUAGES CXX C)

# Set C/C++ standard
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add your sources
add_executable(main
  Source/Private/main.cpp
  Source/Private/shader.cpp
)

# Include directories
target_include_directories(main
  PRIVATE
  Include
  Source/Public
)

if(MSVC)
target_compile_options(main
  PRIVATE
  /permissive-
  /Wall
)
endif()

# Link directories
target_link_directories(main
  PRIVATE
  Libs
)

# Link libraries
target_link_libraries(main
  PRIVATE
  glad.lib
  glfw3.lib
  opengl32.lib
  gdi32.lib
  user32.lib
  shell32.lib
)
