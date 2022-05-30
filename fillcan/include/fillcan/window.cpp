#include "window.hpp"

namespace fillcan
{
    Window::Window(Instance* pInstance, uint32_t width, uint32_t height, std::string name) : width{width}, height{height}, name{name} 
    {
        initWindow();
    }
    
    Window::~Window()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Window::initWindow()
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    }

    bool Window::shouldClose()
    {
        return glfwWindowShouldClose(window); 
    }
}