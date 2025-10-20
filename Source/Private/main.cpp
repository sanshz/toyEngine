#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const char* vertexShaderSource 
{
  "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "void main()\n"
  "{\n"
  "  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
  "}\0"
};

const char* fragmentShaderSourceA
{
  "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  "  FragColor = vec4(0.3568f, 0.5294f, 0.6470f, 1.0f);\n"
  "}\0"
};

const char* fragmentShaderSourceB
{
  "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  "  FragColor = vec4(0.5411f, 0.8039f, 0.9803f, 1.0f);\n"
  "}\0"
};

int main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window {glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL)};
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

  unsigned int vertexShader {glCreateShader(GL_VERTEX_SHADER)};
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if(!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  unsigned int fragmentShaderA {glCreateShader(GL_FRAGMENT_SHADER)};
  glShaderSource(fragmentShaderA, 1, &fragmentShaderSourceA, NULL);
  glCompileShader(fragmentShaderA);

  glGetShaderiv(fragmentShaderA, GL_COMPILE_STATUS, &success);
  if(!success)
  {
    glGetShaderInfoLog(fragmentShaderA, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  unsigned int fragmentShaderB {glCreateShader(GL_FRAGMENT_SHADER)};
  glShaderSource(fragmentShaderB, 1, &fragmentShaderSourceB, NULL);
  glCompileShader(fragmentShaderB);

  unsigned int shaderProgramA {glCreateProgram()};
  glAttachShader(shaderProgramA, vertexShader);
  glAttachShader(shaderProgramA, fragmentShaderA);
  glLinkProgram(shaderProgramA);

  glGetProgramiv(shaderProgramA, GL_LINK_STATUS, &success);
  if(!success)
  {
    glGetProgramInfoLog(shaderProgramA, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << std::endl;
  }

  unsigned int shaderProgramB {glCreateProgram()};
  glAttachShader(shaderProgramB, vertexShader);
  glAttachShader(shaderProgramB, fragmentShaderB);
  glLinkProgram(shaderProgramB);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShaderA);
  glDeleteShader(fragmentShaderB);

  float vertices[]
  {
    -0.9f,  0.8f, 0.0f,
    -0.1f,  0.8f, 0.0f,
    -0.7f,  0.6f, 0.0f,
    -0.1f,  0.6f, 0.0f,
    -0.5f,  0.1f, 0.0f,
    -0.1f,  0.1f, 0.0f,
    -0.5f, -0.1f, 0.0f,
    -0.3f, -0.1f, 0.0f,
    -0.7f, -0.6f, 0.0f,
    -0.3f, -0.6f, 0.0f,
    -0.9f, -0.8f, 0.0f,
    -0.1f, -0.8f, 0.0f,
     0.1f,  0.8f, 0.0f,
     0.3f,  0.8f, 0.0f,
     0.3f, -0.6f, 0.0f,
     0.9f, -0.6f, 0.0f,
     0.1f, -0.8f, 0.0f,
     0.9f, -0.8f, 0.0f
  };
  unsigned int indicesA[]
  {
     1,  3,  2,
     2,  0, 10,
    10,  8, 11,
    11,  9,  7,
     7,  5,  4,
    12, 16, 14,
    14, 15, 17,
  };
  unsigned int indicesB[]
  {
     1,  0,  2,
     2, 10,  8,
     8,  9, 11,
    11,  5,  7,
     7,  6,  4,
    12, 13, 14,
    14, 16, 17
  };

  unsigned int VAO[2];
  unsigned int VBO[2];
  unsigned int EBO[2];
  glGenVertexArrays(2, VAO);
  glGenBuffers(2, VBO);
  glGenBuffers(2, EBO);

  glBindVertexArray(VAO[0]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesA), indicesA, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(VAO[1]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesB), indicesB, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

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

    glUseProgram(shaderProgramA);
    glBindVertexArray(VAO[0]);
    glDrawElements(GL_TRIANGLES, 21, GL_UNSIGNED_INT, 0);

    glUseProgram(shaderProgramB);
    glBindVertexArray(VAO[1]);
    glDrawElements(GL_TRIANGLES, 21, GL_UNSIGNED_INT, 0);

    // check and call events and swap the buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glDeleteVertexArrays(2, VAO);
  glDeleteBuffers(2, VBO);
  glDeleteBuffers(2, EBO);
  glDeleteProgram(shaderProgramA);
  glDeleteProgram(shaderProgramB);

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
