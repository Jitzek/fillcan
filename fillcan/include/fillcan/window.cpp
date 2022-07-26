// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/window.hpp>

// glfw
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace fillcan {
    Window::Window(unsigned int width, unsigned int height, std::string name) : width{width}, height{height}, name{name} { initWindow(); }

    Window::~Window() {
        if (this->pInstance != nullptr) {
            vkDestroySurfaceKHR(this->pInstance->getInstanceHandle(), this->hSurface, nullptr);
        }
        glfwDestroyWindow(this->pWindow);
        glfwTerminate();
    }

    void Window::initWindow() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        pWindow = glfwCreateWindow(this->width, this->height, this->name.c_str(), nullptr, nullptr);
        glfwSetWindowUserPointer(this->pWindow, this);
        glfwSetFramebufferSizeCallback(this->pWindow, framebufferResizeCallback);
    }

    bool Window::shouldClose() { return glfwWindowShouldClose(pWindow); }

    bool Window::wasResized() {
        bool returnValue = this->framebufferResized;
        this->framebufferResized = false;
        return returnValue;
    }

    void Window::pollEvents() { glfwPollEvents(); }

    std::vector<const char*> Window::getRequiredExtensions() {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        return std::vector<const char*>(glfwExtensions, glfwExtensions + glfwExtensionCount);
    }

    void Window::createSurface(Instance* pInstance) {
        if (glfwCreateWindowSurface(pInstance->getInstanceHandle(), this->pWindow, nullptr, &this->hSurface) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create window surface");
        }
        this->pInstance = pInstance;
    }
    VkSurfaceKHR Window::getSurface() { return this->hSurface; }

    VkExtent2D Window::getExtent() { return {.width = this->width, .height = this->height}; }

    void Window::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
        auto pWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        pWindow->framebufferResized = true;
        pWindow->width = width;
        pWindow->height = height;
    }
} // namespace fillcan