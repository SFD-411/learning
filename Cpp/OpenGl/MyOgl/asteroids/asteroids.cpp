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
#include "resources/logic.h"

struct dimensions{
const int width = 1260;
const int height = 720;} screen;

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}


int main (){
  cube cube;
  bullet bullet;

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
  unsigned int cubeprogram = glCreateProgram();
  unsigned int bulletprogram = glCreateProgram();

  glEnable(GL_DEPTH_TEST);
  // glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
  glEnable(GL_MULTISAMPLE);
  glEnable(GL_DITHER);
  glEnable(GL_LINE_SMOOTH);
  // glEnable(GL_CULL_FACE);

  // creates and binds vertex, array and element buffers
  unsigned int cVBO, cVAO, cEBO;
  unsigned int bVBO, bVAO, bEBO;
  glGenVertexArrays(1, &cVAO);
  glGenBuffers(1, &cVBO);
  glGenBuffers(1, &cEBO);

  glBindVertexArray(cVAO);
  glBindBuffer(GL_ARRAY_BUFFER, cVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cube.vertices), cube.vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube.indices), cube.indices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,sizeof(float) * 6, (void*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,sizeof(float) * 6, (void*)(3* sizeof(float)));

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glGenVertexArrays(1, &bVAO);
  glGenBuffers(1, &bVBO);
  glGenBuffers(1, &bEBO);

  glBindVertexArray(bVAO);
  glBindBuffer(GL_ARRAY_BUFFER, bVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(bullet.vertices), bullet.vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(bullet.indices), bullet.indices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,sizeof(float) * 6, (void*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,sizeof(float) * 6, (void*)(3* sizeof(float)));

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // shader data
  ShaderSource source = parseShader("resources/base.shader");
  unsigned int shader = createShader(source.VertexSource, source.FragmentSource, program);
  unsigned int cubeshader = createShader(source.VertexSource, source.FragmentSource, cubeprogram);
  unsigned int bulletshader = createShader(source.VertexSource, source.FragmentSource, bulletprogram);
  int location = glGetUniformLocation(cubeshader, "u_Color");
  float r = 0.1f;
  float g = 0.3f;
  float b = 0.6f;
  float a = 0.5f;
  float rotator = 1.0f;
  float radian = -180.0f;
  float x, y, z;
  bool reverse = false;


  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glm::mat4 view = glm::mat4(1.0f);

  // while we have a window, process ui, refresh buffer and draw objects.
  while(!glfwWindowShouldClose(window))
  {
    camera.mPress = false;

    // calculates time based effects for f-shader
     float timeVal = glfwGetTime();
    float colorVar = sin(timeVal) / 2.0f;
    float red = r + colorVar / 2;
    float green = g - (g * colorVar) / 2;
    float blue = (b * colorVar) * 2;
    glUniform4f(location, red, green - g, blue, a);

    // creates window and runs shader program
    userInput(window);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader);
    glUseProgram(cubeshader);
    glUseProgram(bulletshader);


    view = glm::lookAt(camera.position, camera.position + camera.front, glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::translate(view, glm::vec3(camera.location.x, camera.location.y, camera.location.z));
    glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, &view[0][0]);


    glm::mat4 projection;
    projection = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, &projection[0][0]);


    glBindVertexArray(cVAO); // binds vertex array object

    // creates 7 cubes based on the cube position
    // and the data in the shader buffer.
    for (unsigned int i = 0; i < 1; i++){
      glm::mat4 cubemodel = glm::mat4(2.25f);
      cubemodel = glm::translate(cubemodel, cube.positions[i]);
      float angle = 20.0f * i;
      float yod = 3.0f + i;
      float zed = float((2.2f + i) * -1) ;
      cubemodel = glm::rotate(cubemodel, glm::radians(radian + angle + i), glm::vec3(x + i, y + yod, z + zed));
      glUniformMatrix4fv(glGetUniformLocation(cubeshader, "model"), 1, GL_FALSE, &cubemodel[0][0]);
      glDrawElements(GL_TRIANGLE_FAN, 72, GL_UNSIGNED_INT, 0);
    }
    
    // adds a degree to the rotation of the cube until it reaches 180, then  flips.
    if (radian == 180.0f){  radian = -180.0f; }
    else{ radian = radian + rotator;   }
    x = x + r;
    y = y + r + r;
    z = z - r;

  glBindVertexArray(bVAO);
  if(camera.mPress){
      glm::mat4 bulletmodel = glm::mat4(2.0f);
      bulletmodel = glm::rotate(bulletmodel, glm::radians(180.0f), camera.direction);
      bulletmodel = glm::translate(bulletmodel, camera.location * 2.0f);
      glUniformMatrix4fv(glGetUniformLocation(bulletshader, "model"), 1, GL_FALSE, &bulletmodel[0][0]);
      glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
  }


    glfwSetCursorPosCallback(window, mouselog); // calls back for the mouse location
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  // erases remaining data and exits the program without errors.
  glDeleteVertexArrays(2, (&cVAO, &bVAO));
  glDeleteBuffers(2, (&cVBO, &bVBO));
  glDeleteBuffers(2, (&cEBO, &bEBO));
  glDeleteProgram(program);
  glfwTerminate();
  return 0;
}
