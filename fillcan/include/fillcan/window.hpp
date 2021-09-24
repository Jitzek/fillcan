#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

// std
#include <string>

namespace fillcan
{
    class FillcanWindow
    {
    private:
        int width;
        int height;
        std::string name;
        GLFWwindow *window;

        void initWindow();
    public:
        FillcanWindow(int width, int height, std::string name);
        ~FillcanWindow();

        /** 
         * Explicitly delete the copy constructor and assignment operator:
         * [FillcanWindow] is a pointer to the glfwWindow, copying [FillcanWindow] would create a copy of a pointer to the glfwWindow.
         * When calling the destructor of [FillcanWindow] the glfwWindow will be terminated aswell leaving a dangling pointer behind.
        */
        FillcanWindow(const FillcanWindow&) = delete;
        FillcanWindow &operator=(const FillcanWindow&) = delete;

        bool shouldClose();
    };   
}