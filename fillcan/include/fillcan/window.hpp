#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/instance/instance.hpp>

// std
#include <string>
#include <vector>

// glfw
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace fillcan {
    class Window {
      private:
        uint32_t width;
        uint32_t height;
        std::string name;
        GLFWwindow* pWindow;

        VkSurfaceKHR hSurface;

        void initWindow();

        bool framebufferResized = false;

        static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

      public:
        Window(unsigned int width, unsigned int height, std::string name);
        ~Window();

        /**
         * Explicitly delete the copy constructor and assignment operator:
         * [Window] is a pointer to the glfwWindow, copying [Window] would create a
         * copy of a pointer to the glfwWindow. When calling the destructor of
         * [Window] the glfwWindow will be terminated aswell leaving a dangling
         * pointer behind.
         */
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        bool shouldClose();
        bool wasResized();
        void pollEvents();

        std::vector<const char*> getRequiredExtensions();

        void createSurface(Instance* pInstance);
        VkSurfaceKHR getSurface();
        VkExtent2D getExtent();
    };
} // namespace fillcan