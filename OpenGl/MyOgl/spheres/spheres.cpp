// g++ spheres.cpp glad.c resources/object.cpp -lglfw3 -ldl -pthread
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

#include "resources/object.h"
#include "resources/ui.h"
#include "resources/shader.h"

struct dimensions{
const int width = 800;
const int height = 700;
} screen;

void framebuffer(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void spherebuffer(unsigned int, unsigned int, FiboSphere);
void drawsphere(unsigned int, FiboSphere);

int main(){
  FiboSphere sphere;
  sphere.populateSphere();

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow* window = glfwCreateWindow(screen.width, screen.height, "!IT'S STARTING TO COME TOGETHER!", NULL, NULL);
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer);
  if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
  glEnable(GL_DEPTH_TEST);
  }


  unsigned int program = glCreateProgram();
  ShaderSource source = parseShader("resources/base.shader");
  unsigned int shader = createShader(source.VertexSource, source.FragmentSource, program);

  // creates and binds vertex, array and element buffers
  unsigned int VAO, VBO;
  spherebuffer(VAO, VBO, sphere);
  glm::mat4 view = glm::mat4(1.0f);

  // while we have a window, process ui, refresh buffer and draw objects.
  while(!glfwWindowShouldClose(window))
  {
    userInput(window);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader);
    glm::mat4 trans = glm::mat4(0.3f);
    trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, 0.0f));
    trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.01f, 0.1f, 0.25f));
    unsigned int transformLoc = glGetUniformLocation(shader, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
    glBindVertexArray(VAO);
    // glDrawArrays(GL_POINTS, 0, 64);
    glDrawArrays(GL_LINE_STRIP, 0, 32);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  // erases remaining data and exits the program without errors.
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  // glDeleteBuffers(1, &EBO);
  glDeleteProgram(program);
  glfwTerminate();
}


void spherebuffer(unsigned int VAO, unsigned int VBO, FiboSphere sphere){
  glGenVertexArrays(1,&VAO);
  glGenBuffers(1,&VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(sphere.vertex), sphere.vertex, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
  glEnableVertexAttribArray(0);
}
