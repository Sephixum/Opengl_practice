#pragma once

#include "ShaderClass.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

class Camera {
private:
  int _width;
  int _height;

  float _pitch;
  float _yaw;

  bool _firstMove;

  float _sensitivity;

  float _lastX;
  float _lastY;

  float _speed;

  glm::vec3 _cameraUp;
  glm::vec3 _cameraPosition;
  glm::vec3 _cameraOrientation;
  glm::mat4 _cameraMatrix;

public:
  explicit Camera(int width, int height, glm::vec3 position,
                  GLFWwindow *window) noexcept;

  auto updateCameraMatrix(float FOV, float nearPlane, float farPlane) noexcept
      -> void;

  auto setCameraMatrixToShader(Shader &shader,
                               const char *uniform) const noexcept -> void;
  auto processInput(GLFWwindow *) noexcept -> void;

  auto getCameraMatrix() const noexcept -> glm::mat4;
};
