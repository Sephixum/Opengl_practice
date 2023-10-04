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
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

// Vertices coordinates
static GLfloat pyramidVertices[]{
    -0.5f, 0.0f, 0.5f,   // COORDS
    0.83f, 0.70f, 0.44f, // COLORS
    0.0f, 0.0f,          // TEXCOORDS
    0.0f, -1.0f, 0.0f,   // NORMALS

    -0.5f, 0.0f, -0.5f,  // COORDS
    0.83f, 0.70f, 0.44f, // COLORS
    0.0f, 5.0f,          // TEXCOORDS
    0.0f, -1.0f, 0.0f,   // NORMALS

    0.5f, 0.0f, -0.5f,   // COORDS
    0.83f, 0.70f, 0.44f, // COLORS
    5.0f, 5.0f,          // TEXCOORDS
    0.0f, -1.0f, 0.0f,   // NORMALS

    0.5f, 0.0f, 0.5f,    // COORDS
    0.83f, 0.70f, 0.44f, // COLORS
    5.0f, 0.0f,          // TEXCOORDS
    0.0f, -1.0f, 0.0f,   // NORMALS
    //---------Bottom side---------

    -0.5f, 0.0f, 0.5f,   // COORDS
    0.83f, 0.70f, 0.44f, // COLORS
    0.0f, 0.0f,          // TEXCOORDS
    -0.8f, 0.5f, 0.0f,   // NORMALS

    -0.5f, 0.0f, -0.5f,  // COORDS
    0.83f, 0.70f, 0.44f, // COLORS
    5.0f, 0.0f,          // TEXCOORDS
    -0.8f, 0.5f, 0.0f,   // NORMALS

    0.0f, 0.8f, 0.0f,    // COORDS
    0.92f, 0.86f, 0.76f, // COLORS
    2.5f, 5.0f,          // TEXCOORDS
    -0.8f, 0.5f, 0.0f,   // NORMALS
    //---------Left Side----------

    -0.5f, 0.0f, -0.5f,  // COORDS
    0.83f, 0.70f, 0.44f, // COLORS
    5.0f, 0.0f,          // TEXCOORDS
    0.0f, 0.5f, -0.8f,   // NORMALS

    0.5f, 0.0f, -0.5f,   // COORDS
    0.83f, 0.70f, 0.44f, // COLORS
    0.0f, 0.0f,          // TEXCOORDS
    0.0f, 0.5f, -0.8f,   // NORMALS

    0.0f, 0.8f, 0.0f,    // COORDS
    0.92f, 0.86f, 0.76f, // COLORS
    2.5f, 5.0f,          // TEXCOORDS
    0.0f, 0.5f, -0.8f,   // NORMALS
    //--------Non-facing side------

    0.5f, 0.0f, -0.5f,   // COORDS
    0.83f, 0.70f, 0.44f, // COLORS
    0.0f, 0.0f,          // TEXCOORDS
    0.8f, 0.5f, 0.0f,    // NORMALS

    0.5f, 0.0f, 0.5f,    // COORDS
    0.83f, 0.70f, 0.44f, // COLORS
    5.0f, 0.0f,          // TEXCOORDS
    0.8f, 0.5f, 0.0f,    // NORMALS

    0.0f, 0.8f, 0.0f,    // COORDS
    0.92f, 0.86f, 0.76f, // COLORS
    2.5f, 5.0f,          // TEXCOORDS
    0.8f, 0.5f, 0.0f,    // NORMALS
    //--------Right side----------

    0.5f, 0.0f, 0.5f,    // COORDS
    0.83f, 0.70f, 0.44f, // COLORS
    5.0f, 0.0f,          // TEXCOORDS
    0.0f, 0.5f, 0.8f,    // NORMALS

    -0.5f, 0.0f, 0.5f,   // COORDS
    0.83f, 0.70f, 0.44f, // COLORS
    0.0f, 0.0f,          // TEXCOORDS
    0.0f, 0.5f, 0.8f,    // NORMALS

    0.0f, 0.8f, 0.0f,    // COORDS
    0.92f, 0.86f, 0.76f, // COLORS
    2.5f, 5.0f,          // TEXCOORDS
    0.0f, 0.5f, 0.8f     // NORMALS

    //-------Facing side----------
};

// Indices for vertices order
static GLuint pyramidIndices[]{
    0,  1,  2,  // Bottom side
    0,  2,  3,  // Bottom side
    4,  6,  5,  // Left side
    7,  9,  8,  // Non-facing side
    10, 12, 11, // Right side
    13, 15, 14  // Facing side
};

static GLfloat lightVertices[]{
    //  COORDINATES    /      COLORS       //  EXPLANATION
    +0.1f, +0.1f, +0.1f, 1.0f, 0.0f, 0.0f, // ...........
    +0.1f, +0.1f, -0.1f, 0.0f, 1.0f, 0.0f, // ...........
    +0.1f, -0.1f, -0.1f, 0.0f, 0.0f, 1.0f, // ...........
    +0.1f, -0.1f, +0.1f, 1.0f, 1.0f, 1.0f, // ...........
    -0.1f, -0.1f, +0.1f, 1.0f, 1.0f, 1.0f, // ...........
    -0.1f, -0.1f, -0.1f, 1.0f, 1.0f, 1.0f, // ...........
    -0.1f, +0.1f, -0.1f, 1.0f, 1.0f, 1.0f, // ...........
    -0.1f, +0.1f, +0.1f, 1.0f, 1.0f, 1.0f, // ...........
};

// Indices for vertices order
static GLuint lightIndices[]{
    0, 3, 2, 2, 1, 0, // front square
    0, 1, 6, 0, 7, 6, // right square
    6, 5, 4, 4, 6, 7, // back square
    5, 2, 3, 3, 4, 5, // left square
    3, 4, 7, 7, 0, 3, // down square
    2, 5, 6, 6, 1, 2, // up square
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

  Shader pyramidShader("resources/shaders/pyramidVertex.glsl",
                       "resources/shaders/pyramidFragment.glsl");
  Shader lightShader("resources/shaders/lightVertex.glsl",
                     "resources/shaders/lightFragment.glsl");

  VAO pyramidVAO;
  pyramidVAO.bind();

  VBO pyramidVBO(pyramidVertices, sizeof(pyramidVertices));

  pyramidVAO.linkVBO(pyramidVBO, 0, 3, GL_FLOAT, 11 * sizeof(GLfloat),
                     (void *)0);
  pyramidVAO.linkVBO(pyramidVBO, 1, 3, GL_FLOAT, 11 * sizeof(GLfloat),
                     (void *)(3 * sizeof(GLfloat)));
  pyramidVAO.linkVBO(pyramidVBO, 2, 2, GL_FLOAT, 11 * sizeof(GLfloat),
                     (void *)(6 * sizeof(GLfloat)));

  EBO pyramidEBO(pyramidIndices, sizeof(pyramidIndices));
  pyramidVAO.unBind();

  VAO lightVAO;
  lightVAO.bind();

  VBO lightVBO(lightVertices, sizeof(lightVertices));

  lightVAO.linkVBO(lightVBO, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void *)0);
  lightVAO.linkVBO(lightVBO, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat),
                   (void *)(3 * sizeof(GLfloat)));

  EBO lightEBO(lightIndices, sizeof(lightIndices));
  lightVAO.unBind();

  Texture redBrickTexture;
  try {
    stbi_set_flip_vertically_on_load(true);
    redBrickTexture = Texture("resources/textures/7.png", GL_TEXTURE_2D,
                              GL_TEXTURE1, GL_UNSIGNED_BYTE);
  } catch (std::runtime_error &e) {
    std::cerr << std::format("Caught and exception : {}", e.what())
              << std::endl;
    std::exit(1);
  }

  glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

  pyramidShader.activate();
  pyramidShader.setTextureUnit("tex0", 1);

  auto pyramidModel = glm::mat4(1.0f);
  pyramidModel = glm::translate(pyramidModel, glm::vec3(0.0f, 0.0f, 0.0f));

  pyramidShader.setMat4("model", pyramidModel);
  pyramidShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
  pyramidShader.setVec3("lightColor", lightColor);
  pyramidShader.deActivate();

  lightShader.activate();

  auto lightModel = glm::mat4(1.0f);
  lightModel = glm::translate(lightModel, glm::vec3(1.0f, 1.0f, 1.2f));
  lightShader.setMat4("model", lightModel);
  lightShader.setVec3("lightColor", lightColor);

  lightShader.deActivate();

  redBrickTexture.activate();
  redBrickTexture.bind();

  Camera camera(WIN_WIDTH, WIN_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f), window);

  float phase{};
  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*
     * camera position is only changed via W A S D
     * how ever camera orientation is a vector showing
     * where we are looking at
     * function "processInput" works for camera position and
     * for camera orientation(where it looks at)
     */

    camera.processInput(window);

    /*
     * brief explanations for less confusion
     * camera has to be updated based on an FOV and etc.
     * after all we set it to shader.
     * we could make fov near and far plane static -
     * just to make it more editable we pass them each
     * loop.
     */
    phase = abs(std::sin(float(glfwGetTime())));
    lightColor.x = phase;
    lightColor.y = phase;
    lightColor.z = phase;

    camera.updateCameraMatrix(90.0f, 0.1f, 100.0f);

    pyramidShader.activate();
    pyramidShader.setVec3("lightColor", lightColor);
    pyramidShader.setMat4("cameraMatrix", camera.getCameraMatrix());
    pyramidVAO.bind();
    pyramidEBO.bind();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    pyramidEBO.unBind();
    pyramidVAO.unBind();
    pyramidShader.deActivate();

    lightShader.activate();
    lightShader.setVec3("lightColor", lightColor);
    lightShader.setMat4("cameraMatrix", camera.getCameraMatrix());
    lightVAO.bind();
    lightEBO.bind();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    lightEBO.unBind();
    lightVAO.unBind();
    lightShader.deActivate();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  redBrickTexture.deleteTexture();
  pyramidVAO.deleteAttr();
  pyramidVBO.deleteBuffer();
  pyramidEBO.deleteBuffer();
  pyramidShader.deleteProgram();

  glfwTerminate();
  return 0;
}
