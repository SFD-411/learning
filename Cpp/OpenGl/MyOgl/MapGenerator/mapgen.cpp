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
#include "resources/character.h"
#include "resources/shader.h"

float vertices[] = { 0, 0, 0, 0, 0, 0 };

struct dimensions{
const int width = 1260;
const int height = 720;} screen;

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

int main (){
  mapgen mapgen;
  cube cube;

  camera.lastX = screen.width / 2;
  camera.lastY = screen.height / 2;

  // initializes windows and perameters
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // creates window, or throws error.
  GLFWwindow* window = glfwCreateWindow(screen.width, screen.height, "!IT'S STARTING TO COME TOGETHER!", NULL, NULL);
  if (window == NULL){
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  // makes current window and enables moving and resizing
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouselog);

  // loads all OpenGL functions
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
      std::cout << "Failed to initialize GLAD" << std::endl;
      return -1;
  }

  unsigned int program = glCreateProgram();

  glEnable(GL_DEPTH_TEST);
  // glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
  glEnable(GL_MULTISAMPLE);
  glEnable(GL_DITHER);
  glEnable(GL_LINE_SMOOTH);
  // glEnable(GL_CULL_FACE);

  // creates and binds vertex, array and element buffers
  unsigned int VBO, VAO /*,EBO*/;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1,&VBO);
  // glGenBuffers(1,&EBO);
  void* vecPtr = &mapgen.mapVectors; 


  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, mapgen.vecCount, vecPtr, GL_STATIC_DRAW);
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube.indices), cube.indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,sizeof(float) * 6, (void*)0);
  glEnableVertexAttribArray(0);
  // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,sizeof(float) * 6, (void*)(3* sizeof(float)));
  // glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // shader data
  ShaderSource source = parseShader("resources/base.shader");
  unsigned int shader = createShader(source.VertexSource, source.FragmentSource, program);


  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glm::mat4 view = glm::mat4(1.0f);

  // while we have a window, process ui, refresh buffer and draw objects.
  while(!glfwWindowShouldClose(window))
  {
    // creates window and runs shader program
    userInput(window);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader);


    view = glm::lookAt(camera.position, camera.front, glm::vec3(0.0f, -1.0f, 0.0f));
    view = glm::translate(view, glm::vec3(camera.location.x, camera.location.y, camera.location.z));
    glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, &view[0][0]);

    glm::mat4 projection;
    projection = glm::perspective(100.0f, 1.0f, 0.1f, 500.0f);
    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, &projection[0][0]);


    glBindVertexArray(VAO); // binds vertex array object
    glDrawArrays(GL_POINTS, 0, mapgen.vecCount);

    // creates 7 cubes based on the cube position
    // and the data in the shader buffer.
    // for (unsigned int i = 0; i < mapgen.mapVectors.size(); i++){
      
    //   glm::mat4 model = glm::mat4(0.15f);
    //   model = glm::translate(model, glm::vec3(mapgen.mapVectors[i].x, ));
    //   glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, &model[0][0]);
    //   glDrawElements(GL_POINTS, mapgen.mapVectors.size(), GL_UNSIGNED_INT, 0);
    // }
    
    glfwSetCursorPosCallback(window, mouselog); // calls back for the mouse location
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  // erases remaining data and exits the program without errors.
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  //glDeleteBuffers(1, &EBO);
  glDeleteProgram(program);
  glfwTerminate();
  return 0;
}
