#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

#include "shader.hpp"

namespace Screen
{
  const unsigned int width {1000};
  const unsigned int height {750};
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window {glfwCreateWindow(Screen::width, Screen::height, "LearnOpenGL", NULL, NULL)};
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  Shader myShader {"../Shaders/shader.vsh", "../Shaders/shader.fsh"};

  float vertices[]
  {
    -0.9f,  0.8f, 0.0f, 1.0f, 0.0f, 0.0f,
    -0.1f,  0.8f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.7f,  0.6f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.1f,  0.6f, 0.0f, 1.0f, 1.0f, 0.0f,
    -0.5f,  0.1f, 0.0f, 0.0f, 1.0f, 1.0f,
    -0.1f,  0.1f, 0.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.1f, 0.0f, 0.5f, 0.0f, 0.0f,
    -0.3f, -0.1f, 0.0f, 0.0f, 0.5f, 0.0f,
    -0.7f, -0.6f, 0.0f, 0.0f, 0.0f, 0.5f,
    -0.3f, -0.6f, 0.0f, 1.0f, 0.5f, 0.0f,
    -0.9f, -0.8f, 0.0f, 0.5f, 1.0f, 0.0f,
    -0.1f, -0.8f, 0.0f, 0.0f, 1.0f, 0.5f,
     0.1f,  0.8f, 0.0f, 0.0f, 0.5f, 1.0f,
     0.3f,  0.8f, 0.0f, 0.5f, 0.0f, 1.0f,
     0.3f, -0.6f, 0.0f, 1.0f, 0.0f, 0.5f,
     0.9f, -0.6f, 0.0f, 1.0f, 0.5f, 0.5f,
     0.1f, -0.8f, 0.0f, 0.5f, 1.0f, 0.5f,
     0.9f, -0.8f, 0.0f, 0.5f, 0.5f, 1.0f
  };
  unsigned int indices[]
  {
     0,  1,  2,
     1,  2,  3,
     2,  8, 10,
     0,  2, 10,
     8,  9, 11,
     8, 10, 11,
     5,  7, 11,
     7,  9, 11,
     4,  6,  7,
     4,  5,  7,
    12, 13, 14,
    12, 14, 16,
    14, 16, 17,
    14, 15, 17
  };

  unsigned int VAO;
  unsigned int VBO;
  unsigned int EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // wireframe polygons
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  while(!glfwWindowShouldClose(window))
  {
    // input
    processInput(window);
    
    // rendering
    glClearColor(0.1725f, 0.2549f, 0.3137f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    myShader.use();

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, std::size(indices), GL_UNSIGNED_INT, 0);

    // swap the buffers and check and call events
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);

  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow* window)
{
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  { glfwSetWindowShouldClose(window, true); }

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{ glViewport(0, 0, width, height); }
