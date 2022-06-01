// fillcan
#include <fillcan/window.hpp>

namespace fillcan {
    Window::Window(unsigned int width, unsigned int height, std::string name) : width{width}, height{height}, name{name} { initWindow(); }

    Window::~Window() {
        glfwDestroyWindow(pWindow);
        glfwTerminate();
    }

    void Window::initWindow() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        pWindow = glfwCreateWindow(this->width, this->height, this->name.c_str(), nullptr, nullptr);
    }

    bool Window::shouldClose() { return glfwWindowShouldClose(pWindow); }

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
    }
    VkSurfaceKHR Window::getSurface() { return this->hSurface; }

    VkExtent2D Window::getExtend() { return {.width = this->width, .height = this->height}; }
} // namespace fillcan