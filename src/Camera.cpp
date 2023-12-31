#include "Camera.hpp"
#include "Globals.hpp"
#include <cmath>
#include <format>

Camera::Camera(int width, int height, glm::vec3 position,
               GLFWwindow *window) noexcept
    : _width(width), _height(height), _cameraPosition(position) {

  _firstMove = true;

  _pitch = 0.0f;
  _yaw = -90.0f;

  _speed = 0.1f;
  _sensitivity = 0.1f;

  _lastX = 0.0f;
  _lastY = 0.0f;

  _cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
  _cameraOrientation = glm::vec3(0.0f, 0.0f, -1.0f);

  _cameraMatrix = glm::mat4(1.0f);
}

auto Camera::updateCameraMatrix(float FOV, float nearPlane,
                                float farPlane) noexcept -> void {

  auto projection =
      glm::perspective(glm::radians(FOV),
                       static_cast<float>(_width) / static_cast<float>(_height),
                       nearPlane, farPlane);
  auto view = glm::lookAt(_cameraPosition, _cameraPosition + _cameraOrientation,
                          _cameraUp);

  _cameraMatrix = projection * view;
}

auto Camera::setCameraMatrixToShader(Shader &shader,
                                     const char *uniform) const noexcept
    -> void {

  glUniformMatrix4fv(glGetUniformLocation(shader.getID(), uniform), 1, GL_FALSE,
                     glm::value_ptr(_cameraMatrix));
}

auto Camera::processInput(GLFWwindow *window) noexcept -> void {

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    _cameraPosition += _speed * _cameraOrientation;
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    _cameraPosition -= _speed * _cameraOrientation;
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    _cameraPosition +=
        _speed * glm::normalize(glm::cross(_cameraUp, _cameraOrientation));
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    _cameraPosition -=
        _speed * glm::normalize(glm::cross(_cameraUp, _cameraOrientation));
  }
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    _cameraPosition += _speed * _cameraUp;
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
    _cameraPosition -= _speed * _cameraUp;
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
    _speed = 0.3f;
  } else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE) {
    _speed = 0.1f;
  }
  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    double xMousePos;
    double yMousePos;
    glfwGetCursorPos(window, &xMousePos, &yMousePos);

    float xPos = static_cast<float>(xMousePos);
    float yPos = static_cast<float>(yMousePos);

    if (_firstMove) {
      _lastX = xPos;
      _lastY = yPos;
      _firstMove = false;
    }

    float xOffset = xPos - _lastX;
    float yOffset = _lastY - yPos;

    _lastX = xPos;
    _lastY = yPos;

    xOffset *= _sensitivity;
    yOffset *= _sensitivity;

    _yaw += xOffset;
    _pitch += yOffset;

    if (_pitch > 89.0f) {
      _pitch = 89.0f;
    }
    if (_pitch < -89.0f) {
      _pitch = -89.0f;
    }

    glm::vec3 newCameraOrientation;
    newCameraOrientation.x =
        std::cos(glm::radians(_yaw)) * std::cos(glm::radians(_pitch));
    newCameraOrientation.y = std::sin(glm::radians(_pitch));
    newCameraOrientation.z =
        std::sin(glm::radians(_yaw)) * std::cos(glm::radians(_pitch));
    _cameraOrientation = newCameraOrientation;
  } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) ==
             GLFW_RELEASE) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    _firstMove = true;
  }
}

auto Camera::getCameraMatrix() const noexcept -> glm::mat4 {
  return _cameraMatrix;
}

auto Camera::getCameraPosition() const noexcept -> glm::vec3 {
  return _cameraPosition;
}
