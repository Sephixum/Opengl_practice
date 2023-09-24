#include "Camera.hpp"
#include "Globals.hpp"
#include <format>

Camera::Camera(int width, int height, glm::vec3 position,
               GLFWwindow *window) noexcept
    : width(width), height(height), cameraPosition(position) {

  _cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
  cameraOrientation = glm::vec3(0.0f, 0.0f, -1.0f);
  speed = 0.1f;
  _sensitivity = 2.5f;
  _firstMove = true;
}

auto Camera::setMatrixToShader(float FOV, float nearPlane, float farPlane,
                               Shader &shaderProgram,
                               const char *uniform) noexcept -> void {

  auto projection = glm::perspective(
      glm::radians(FOV), static_cast<float>(width) / static_cast<float>(height),
      nearPlane, farPlane);
  auto view = glm::lookAt(cameraPosition, cameraPosition + cameraOrientation,
                          _cameraUp);

  glUniformMatrix4fv(glGetUniformLocation(shaderProgram.getID(), uniform), 1,
                     GL_FALSE, glm::value_ptr(projection * view));
}

auto Camera::processInput(GLFWwindow *window) noexcept -> void {

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    cameraPosition += speed * cameraOrientation;
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    cameraPosition -= speed * cameraOrientation;
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    cameraPosition +=
        speed * glm::normalize(glm::cross(_cameraUp, cameraOrientation));
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    cameraPosition -=
        speed * glm::normalize(glm::cross(_cameraUp, cameraOrientation));
  }
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    cameraPosition += speed * _cameraUp;
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
    cameraPosition -= speed * _cameraUp;
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
    speed = 0.3f;
  } else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE) {
    speed = 0.1f;
  }
  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
    double xMousePos;
    double yMousePos;
    glfwGetCursorPos(window, &xMousePos, &yMousePos);

    if (_firstMove) {
      _lastX = xMousePos;
      _lastY = yMousePos;
      _firstMove = false;
    }
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    float xOffSet = xMousePos - _lastX;
    float yOffSet = yMousePos - _lastY;

    _lastX = xMousePos;
    _lastY = yMousePos;

    xOffSet *= speed;
    yOffSet *= speed;

    _rotationByY += xOffSet;
    _rotationByX += yOffSet;

    if (_rotationByX > 89.f) {
      yOffSet = 0;
      _rotationByX = 89.f;
    }
    if (_rotationByX < -89.f) {
      yOffSet = 0;
      _rotationByX = -89.f;
    }
    if (_rotationByY > 360.f) {
      xOffSet = 0;
      _rotationByY = 0;
    }
    if (_rotationByY < -360.f) {
      xOffSet = 0;
      _rotationByY = 0;
    }
    glm::vec3 cameraRight =
        glm::normalize(glm::cross(cameraOrientation, _cameraUp));
    glm::vec3 _cameraUp =
        glm::normalize(glm::cross(cameraOrientation, cameraRight));
    cameraOrientation =
        glm::rotate(cameraOrientation, glm::radians(yOffSet),
                    glm::normalize(glm::cross(cameraOrientation, _cameraUp)));
    cameraOrientation =
        glm::rotate(cameraOrientation, glm::radians(xOffSet), _cameraUp);
    std::cout << _rotationByY << '\n';

  } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) ==
             GLFW_RELEASE) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    _firstMove = true;
  }
}
