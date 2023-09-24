#pragma once

#include "ShaderClass.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

class Camera {
private:
  float _rotationByX;
  float _rotationByY;

  bool _firstMove;

  float _sensitivity;

  float _lastX;
  float _lastY;

  glm::vec3 _cameraUp;

public:
  explicit Camera(int width, int height, glm::vec3 position,
                  GLFWwindow *window) noexcept;

  auto setMatrixToShader(float FOV, float nearPlane, float farPlane,
                         Shader &shaderProgram, const char *uniform) noexcept
      -> void;
  auto processInput(GLFWwindow *) noexcept -> void;

  glm::vec3 cameraPosition;
  glm::vec3 cameraOrientation;

  int width;
  int height;
  float speed;
};
