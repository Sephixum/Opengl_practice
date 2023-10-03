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
#include <format>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

// Vertices coordinations
GLfloat cubeVertices[]{
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
GLuint cubeIndices[]{
    0, 3, 2, 2, 1, 0, //// front square
    0, 1, 6, 0, 7, 6, //// right square
    6, 5, 4, 4, 6, 7, //// back square
    5, 2, 3, 3, 4, 5, //// left square
    3, 4, 7, 7, 0, 3, //// down square
    2, 5, 6, 6, 1, 2, //// up square
};

GLfloat lightVertices[]{
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
GLuint lightIndices[]{
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

  Shader cubeShader("resources/shaders/cube.vs", "resources/shaders/cube.fs");
  Shader lightShader("resources/shaders/cube.vs", "resources/shaders/cube.fs");

  VAO cubeVAO;
  cubeVAO.bind();

  VBO cubeVBO(cubeVertices, sizeof(cubeVertices));

  cubeVAO.linkVBO(cubeVBO, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), 0);
  cubeVAO.linkVBO(cubeVBO, 1, 3, GL_FLOAT, 8 * sizeof(GLfloat),
                  (void *)(3 * sizeof(GLfloat)));
  cubeVAO.linkVBO(cubeVBO, 2, 2, GL_FLOAT, 8 * sizeof(GLfloat),
                  (void *)(6 * sizeof(GLfloat)));

  EBO cubeEBO(cubeIndices, sizeof(cubeIndices));
  cubeEBO.bind();

  cubeVAO.unBind();

  Texture pop_catTexture;
  Texture smilingEmoji;
  try {
    stbi_set_flip_vertically_on_load(true);
    pop_catTexture = Texture("resources/textures/3.png", GL_TEXTURE_2D,
                             GL_TEXTURE0, GL_UNSIGNED_BYTE);
    smilingEmoji = Texture("resources/textures/2.png", GL_TEXTURE_2D,
                           GL_TEXTURE1, GL_UNSIGNED_BYTE);
  } catch (std::runtime_error &e) {
    std::cout << std::format("Caught and exception : {}", e.what())
              << std::endl;
    std::exit(1);
  }

  pop_catTexture.setTextureUnit(cubeShader, "tex0", 0);
  smilingEmoji.setTextureUnit(cubeShader, "tex1", 1);

  std::vector<glm::vec3> cubePositions{
      glm::vec3(2.0f, 2.0f, 2.0f),   glm::vec3(-2.0f, -2.0f, -2.0f),
      glm::vec3(-1.0f, 2.0f, -6.0f), glm::vec3(6.0f, -3.0f, 1.0f),
      glm::vec3(3.0f, -5.0f, 4.0f),  glm::vec3(2.8f, -6.0f, 1.0f),
      glm::vec3(4.0f, -3.0f, 4.0f),
  };

  cubeShader.activate();

  auto model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
  glUniformMatrix4fv(glGetUniformLocation(cubeShader.getID(), "model"), 1,
                     GL_FALSE, glm::value_ptr(model));

  pop_catTexture.activate();
  pop_catTexture.bind();
  smilingEmoji.activate();
  smilingEmoji.bind();

  Camera camera(WIN_WIDTH, WIN_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f), window);

  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     /* camera position is only changed via W A S D
      * how ever camera orientation is a vector showing
      * where we are looking at
      */

    camera.processInput(window);

    /*
     * small explanations for less confusion
     * camera has to be updated based on an FOV and etc
     * and after all we set it to shader
     */

    camera.updateCameraMatrix(90.0f, 0.1f, 100.0f);
    camera.setCameraMatrixToShader(cubeShader, "cameraMatrix");

    // render stuff
    cubeVAO.bind();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    cubeVAO.unBind();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  pop_catTexture.deleteTexture();
  smilingEmoji.deleteTexture();
  cubeVAO.deleteAttr();
  cubeVBO.deleteBuffer();
  cubeEBO.deleteBuffer();
  cubeShader.deleteProgram();

  glfwTerminate();
  return 0;
}
