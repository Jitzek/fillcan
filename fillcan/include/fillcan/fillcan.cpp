#include "fillcan/device_pool.hpp"
#include "fillcan/window.hpp"
#include <fillcan/fillcan.hpp>
#include <fillcan/instance.hpp>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

namespace fillcan {

std::vector<const char*> requiredInstanceLayers = {
#ifndef NDEBUG
    "VK_LAYER_KHRONOS_validation"
#endif
};

std::vector<const char*> requiredInstanceExtensions = {
#ifndef NDEBUG
    VK_EXT_DEBUG_UTILS_EXTENSION_NAME
#endif
};

std::vector<const char*> requiredDeviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

Fillcan::Fillcan(const char* pApplicationName, uint32_t applicationVersion, unsigned int windowWidth, unsigned int windowHeight) {
    // Initialize Window
    this->upWindow = std::make_unique<Window>(windowWidth, windowHeight, pApplicationName);

    // Initialize Instance
    std::vector<const char*> windowExtensions = upWindow->getRequiredExtensions();
    requiredInstanceExtensions.insert(requiredInstanceExtensions.begin(), windowExtensions.begin(), windowExtensions.end());
    this->upInstance = std::make_unique<Instance>(pApplicationName, applicationVersion, requiredInstanceLayers, requiredInstanceExtensions);

    // Initialize Device Pool
    this->upDevicePool = std::make_unique<DevicePool>(this->upInstance.get(), this->upWindow.get(), requiredDeviceExtensions);
}

Fillcan::~Fillcan() {}

void Fillcan::MainLoop(std::function<void()> callback) {
    while (!upWindow->shouldClose()) {
        glfwPollEvents();

        callback();
    }
}

} // namespace fillcan