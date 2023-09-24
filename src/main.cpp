#include "Camera.hpp"
#include "EBO.hpp"
#include "Globals.hpp"
#include "ShaderClass.hpp"
#include "Textures.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "stb_image.h"

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

// Vertices coordinations
GLfloat vertices[]{
    //  COORDINATES    /      COLORS     /  TEXCOORDS  //  EXPLANATION
    +0.5f, +0.5f, +0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // ...........
    +0.5f, +0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // ...........
    +0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // ...........
    +0.5f, -0.5f, +0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // ...........
    -0.5f, -0.5f, +0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // ...........
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // ...........
    -0.5f, +0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // ...........
    -0.5f, +0.5f, +0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // ...........
};

// Indices for vertices order
GLuint indices[]{
    0, 3, 2, 2, 1, 0, //// front square
    0, 1, 6, 0, 7, 6, //// right square
    6, 5, 4, 4, 6, 7, //// back square
    5, 2, 3, 3, 4, 5, //// left square
    3, 4, 7, 7, 0, 3, //// down square
    2, 5, 6, 6, 1, 2, //// up square
};

auto processInput(GLFWwindow *window) -> void {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, 1);
  }
}

auto main() -> int {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  auto window =
      glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Test window", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to initialize GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }
  glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
  glfwSetFramebufferSizeCallback(
      window, [](GLFWwindow *window, int width, int height) -> void {
        glViewport(0, 0, width, height);
      });

  glEnable(GL_DEPTH_TEST);

  Shader shaderProgram("resources/shaders/vert.glsl",
                       "resources/shaders/frag.glsl");

  VAO vertexAttributes;
  vertexAttributes.bind();

  VBO vertexBuffer(vertices, sizeof(vertices));

  vertexAttributes.linkVBO(vertexBuffer, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat),
                           0);
  vertexAttributes.linkVBO(vertexBuffer, 1, 3, GL_FLOAT, 8 * sizeof(GLfloat),
                           (void *)(3 * sizeof(GLfloat)));
  vertexAttributes.linkVBO(vertexBuffer, 2, 2, GL_FLOAT, 8 * sizeof(GLfloat),
                           (void *)(6 * sizeof(GLfloat)));

  EBO indicesBuffer(indices, sizeof(indices));
  indicesBuffer.bind();

  vertexAttributes.unBind();

  stbi_set_flip_vertically_on_load(true);
  Texture pop_catTexture("resources/textures/3.png", GL_TEXTURE_2D, GL_TEXTURE0,
                         GL_UNSIGNED_BYTE);
  Texture smilingEmoji("resources/textures/2.png", GL_TEXTURE_2D, GL_TEXTURE1,
                       GL_UNSIGNED_BYTE);

  pop_catTexture.setTextureUnit(shaderProgram, "tex0", 0);
  smilingEmoji.setTextureUnit(shaderProgram, "tex1", 1);

  Camera camera(WIN_WIDTH, WIN_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f), window);

  std::vector<glm::vec3> cubePositions{
      glm::vec3(2.0f, 2.0f, 2.0f),   glm::vec3(-2.0f, -2.0f, -2.0f),
      glm::vec3(-1.0f, 2.0f, -6.0f), glm::vec3(6.0f, -3.0f, 1.0f),
      glm::vec3(3.0f, -5.0f, 4.0f),  glm::vec3(2.8f, -6.0f, 1.0f),
      glm::vec3(4.0f, -3.0f, 4.0f),
  };

  auto model = glm::mat4(1.0f);

  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderProgram.activate();
    pop_catTexture.activate();
    pop_catTexture.bind();
    smilingEmoji.activate();
    smilingEmoji.bind();
    camera.matrix(66.0f, 0.1f, 100.0f, shaderProgram, "cameraMatrix");
    camera.processInput(window);

    // render stuff
    vertexAttributes.bind();
    for (int i = 0; i < cubePositions.size(); i++) {
      model = glm::mat4(1.0f);
      float angle = 20 * i;
      model =
          glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 1.0f, 1.0f));
      model = glm::translate(model, cubePositions[i]);

      glUniformMatrix4fv(glGetUniformLocation(shaderProgram.getID(), "model"),
                         1, GL_FALSE, glm::value_ptr(model));

      glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }
    vertexAttributes.unBind();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  pop_catTexture.deleteTexture();
  smilingEmoji.deleteTexture();
  vertexAttributes.deleteAttr();
  vertexBuffer.deleteBuffer();
  indicesBuffer.deleteBuffer();
  shaderProgram.deleteProgram();

  glfwTerminate();
  return 0;
}
