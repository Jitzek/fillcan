#include "fillcan/window.hpp"
#include <fillcan/fillcan.hpp>
#include <fillcan/instance.hpp>
#include <iostream>
#include <thread>

namespace fillcan {
Fillcan::Fillcan(const char *pApplicationName, uint32_t applicationVersion)
    : instance(pApplicationName, applicationVersion, {}, {}),
      window(&instance, 800, 600, pApplicationName) {
    
}

Fillcan::~Fillcan() {}

void Fillcan::MainLoop(std::function<void()> callback) {
  while (!window.shouldClose()) {
    glfwPollEvents();

    callback();
  }
}

} // namespace fillcan