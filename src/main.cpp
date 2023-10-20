#include "Camera.hpp"
#include "EBO.hpp"
#include "Globals.hpp"
#include "ShaderClass.hpp"
#include "Shapes.hpp"
#include "Textures.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "stb_image.h"

#include <GLFW/glfw3.h>
#include <cmath>
#include <format>
#include <glm/ext/matrix_transform.hpp>
#include <iostream>

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
      glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Test window", nullptr, nullptr);
  if (window == nullptr) {
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

  VBO pyramidVBO(shape::pyramidVertices.data(),
                 shape::pyramidVertices.size() * sizeof(GLfloat)); // NOLINT(*-narrowing-conversions)

  pyramidVAO.linkVBO(pyramidVBO, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat),
                     (void *)nullptr);
  pyramidVAO.linkVBO(pyramidVBO, 1, 2, GL_FLOAT, 8 * sizeof(GLfloat),
                     (void *)(3 * sizeof(GLfloat)));
  pyramidVAO.linkVBO(pyramidVBO, 2, 3, GL_FLOAT, 8 * sizeof(GLfloat),
                     (void *)(5 * sizeof(GLfloat)));

  EBO pyramidEBO(shape::pyramidIndices.data(),
                 shape::pyramidIndices.size() * sizeof(GLuint));
  pyramidVAO.unBind();

  VAO lightVAO;
  lightVAO.bind();

  VBO lightVBO(shape::lightVertices.data(),
               shape::lightVertices.size() * sizeof(GLfloat));

  lightVAO.linkVBO(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(GLfloat),
                   (void *)nullptr);

  EBO lightEBO(shape::lightIndices.data(),
               shape::lightIndices.size() * sizeof(GLfloat));
  lightVAO.unBind();

  Texture redBrickTexture{};
  try {
    stbi_set_flip_vertically_on_load(true);
    redBrickTexture = Texture("resources/textures/7.png", GL_TEXTURE_2D,
                              GL_TEXTURE1, GL_UNSIGNED_BYTE);
  } catch (std::runtime_error &e) {
    std::cerr << std::format("Caught and exception : {}", e.what())
              << std::endl;
    stbi_set_flip_vertically_on_load(true);
    std::exit(1);
  }

  glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
  glm::vec3 lightPosition(0.5f, 0.5f, 0.5f);
  glm::vec3 objectColor(1.f, 1.f, 1.f);

  pyramidShader.activate();
  pyramidShader.setTextureUnit("tex0", 1);

  auto pyramidModel = glm::mat4(1.0f);
  pyramidModel = glm::translate(pyramidModel, glm::vec3(0.0f, 0.0f, 0.0f));

  pyramidShader.setMat4("model", pyramidModel);
  pyramidShader.setVec3("objectColor", objectColor);

  pyramidShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
  pyramidShader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
  pyramidShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
  pyramidShader.setFloat("material.shininess", 32.0f);

  pyramidShader.setVec3("light.position", lightPosition);
  pyramidShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
  pyramidShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
  pyramidShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
  Shader::deActivate();

  lightShader.activate();

  glm::mat4 lightModel(1.0f);
  lightModel = glm::translate(lightModel, lightPosition);
  lightShader.setMat4("model", lightModel);
  lightShader.setVec3("lightColor", lightColor);
  Shader::deActivate();

  redBrickTexture.activate();
  redBrickTexture.bind();

  Camera camera(WIN_WIDTH, WIN_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f), window);

  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*
     * camera position is only changed via W A S D
     * however camera orientation is a vector showing
     * where we are looking at
     * function "processInput" works for camera position and
     * for camera orientation(where it looks at)
     */

    camera.processInput(window);

    /*
     * brief explanations for less confusion
     * camera has to be updated based on an FOV etc.
     * after all we set it to shader.
     * we could make fov near and far plane static -
     * just to make it more editable we pass them each
     * loop.
     */

    auto radius = 3.0f;
    auto x = radius * std::cos((glfwGetTime()));
//    auto y = radius * std::cos((glfwGetTime()));
    auto z = radius * std::sin((glfwGetTime()));
    lightPosition = glm::vec3(x, 2.0f, z);

    camera.updateCameraMatrix(90.0f, 0.1f, 100.0f);

    pyramidShader.activate();
    pyramidShader.setMat4("cameraMatrix", camera.getCameraMatrix());
    pyramidShader.setVec3("light.position", lightPosition);
    pyramidShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
    pyramidShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
    pyramidShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
    pyramidShader.setVec3("viewPos", camera.getCameraPosition());
    pyramidVAO.bind();
    pyramidEBO.bind();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
    pyramidEBO.unBind();
    pyramidVAO.unBind();
    Shader::deActivate();

    lightShader.activate();
    lightShader.setMat4("cameraMatrix", camera.getCameraMatrix());
    lightModel = glm::mat4(1.0f);
    lightModel = glm::scale(lightModel, glm::vec3(0.3, 0.3, 0.3));
    lightModel = glm::translate(lightModel, lightPosition);
    lightShader.setMat4("model", lightModel);
    lightVAO.bind();
    lightEBO.bind();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
    lightEBO.unBind();
    lightVAO.unBind();
    Shader::deActivate();

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
