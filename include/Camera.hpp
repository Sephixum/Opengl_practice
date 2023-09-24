#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "ShaderClass.hpp"

class Camera {
public:
  Camera(int width, int height, glm::vec3 position, GLFWwindow *window);

  auto setMatrixToShader(float FOV, float nearPlane, float farPlane, Shader &shaderProgram,
              const char *uniform) -> void;
  auto processInput(GLFWwindow *) -> void;

  glm::vec3 cameraPosition;
  glm::vec3 cameraOrientation;
  glm::vec3 cameraUp;

  int width;
  int height;
  float speed;
  bool firstMove;

  float lastX;
  float lastY;

  float rotX;
  float rotY;
  float sensitivity;
};
