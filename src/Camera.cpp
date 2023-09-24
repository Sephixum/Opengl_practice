#include "Camera.hpp"
#include "Globals.hpp"

Camera::Camera(int width, int height, glm::vec3 position, GLFWwindow *window)
    : width(width), height(height), cameraPosition(position) {
  cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
  cameraOrientation = glm::vec3(0.0f, 0.0f, -1.0f);
  speed = 0.1f;
  sensitivity = 2.5f;
  firstMove = true;
}

auto Camera::setMatrixToShader(float FOV, float nearPlane, float farPlane,
                    Shader &shaderProgram, const char *uniform) -> void {
  auto projection = glm::perspective(
      glm::radians(FOV), static_cast<float>(width) / static_cast<float>(height),
      nearPlane, farPlane);
  auto view =
      glm::lookAt(cameraPosition, cameraPosition + cameraOrientation, cameraUp);

  glUniformMatrix4fv(glGetUniformLocation(shaderProgram.getID(), uniform), 1,
                     GL_FALSE, glm::value_ptr(projection * view));
}

auto Camera::processInput(GLFWwindow *window) -> void {
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    cameraPosition += speed * cameraOrientation;
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    cameraPosition -= speed * cameraOrientation;
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    cameraPosition +=
        speed * glm::normalize(glm::cross(cameraUp, cameraOrientation));
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    cameraPosition -=
        speed * glm::normalize(glm::cross(cameraUp, cameraOrientation));
  }
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    cameraPosition += speed * cameraUp;
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
    cameraPosition -= speed * cameraUp;
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

    if (firstMove) {
      lastX = xMousePos;
      lastY = yMousePos;
      firstMove = false;
    }
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    float xOffSet = xMousePos - lastX;
    float yOffSet = yMousePos - lastY;

    lastX = xMousePos;
    lastY = yMousePos;

    xOffSet *= speed;
    yOffSet *= speed;

    rotY += xOffSet;
    rotX += yOffSet;

    if (rotX > 89.f) {
      yOffSet = 0;
      rotX = 89.f;
    }
    if (rotX < -89.f) {
      yOffSet = 0;
      rotX = -89.f;
    }
    if (rotY > 360.f) {
      xOffSet = 0;
      rotY = 0;
    }
    if (rotY < -360.f) {
      xOffSet = 0;
      rotY = 0;
    }
    glm::vec3 cameraRight =
        glm::normalize(glm::cross(cameraOrientation, cameraUp));
    glm::vec3 cameraUp =
        glm::normalize(glm::cross(cameraOrientation, cameraRight));
    cameraOrientation =
        glm::rotate(cameraOrientation, glm::radians(yOffSet),
                    glm::normalize(glm::cross(cameraOrientation, cameraUp)));
    cameraOrientation =
        glm::rotate(cameraOrientation, glm::radians(xOffSet), cameraUp);

  } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) ==
             GLFW_RELEASE) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    firstMove = true;
  }
}
