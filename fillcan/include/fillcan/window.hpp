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
        Instance* pInstance;

        VkSurfaceKHR hSurface;

        void initWindow();

        bool framebufferResized = false;

        static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

      public:
        /**
         * @brief Create a new Window.
         *
         * @param width The initial width of the Window.
         * @param height The initial height of the Window.
         * @param name The name of the Window.
         */
        Window(unsigned int width, unsigned int height, std::string name);
        ~Window();
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        /**
         * @brief Whether the Window should close, e.g. the user attempts to close it.
         *
         * @return true if the Window should close.
         * @return false if the Window shouldn't close.
         */
        bool shouldClose();

        /**
         * @brief Whether the Window was resized.
         *
         * @return true if the Window was resized.
         * @return false if the Window wasn't resized.
         */
        bool wasResized();

        /**
         * @brief Poll for events, e.g. close button pressed, window resized or other user interaction.
         */
        void pollEvents();

        /**
         * @brief Get a list of required extensions that should be enabled by Vulkan.
         *
         * @return A list of the required extensions.
         */
        std::vector<const char*> getRequiredExtensions();

        /**
         * @brief Create a Vulkan Surface using the Instance, @see Instance.
         *
         * @param pInstance A pointer to the Instance to create a surface with.
         */
        void createSurface(Instance* pInstance);

        /**
         * @brief Get the Vulkan Surface created with @see Window#createSurface.
         *
         * @return A handle to the created Vulkan Surface.
         */
        VkSurfaceKHR getSurface();

        /**
         * @brief Get the Extent of the Window.
         *
         * @return The Extent of the Window.
         */
        VkExtent2D getExtent();
    };
} // namespace fillcan