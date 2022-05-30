#pragma once

// fillcan

// std
#include <fillcan/instance.hpp>
#include <array>
#include <string>
#include <iostream>

// glfw
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace fillcan {
class Window {
private:
  uint32_t width;
  uint32_t height;
  std::string name;
  GLFWwindow *window;

  void initWindow();

public:
  Window(Instance* pInstance, uint32_t width, uint32_t height, std::string name);
  ~Window();

  /**
   * Explicitly delete the copy constructor and assignment operator:
   * [Window] is a pointer to the glfwWindow, copying [Window] would create a
   * copy of a pointer to the glfwWindow. When calling the destructor of
   * [Window] the glfwWindow will be terminated aswell leaving a dangling
   * pointer behind.
   */
  Window(const Window &) = delete;
  Window &operator=(const Window &) = delete;

  bool shouldClose();
};
} // namespace fillcan