#include "window.hpp";

namespace fillcan
{
    FillcanWindow::FillcanWindow(int width, int height, std::string name) : width{width}, height{height}, name{name} 
    {
        initWindow();
    }
    
    FillcanWindow::~FillcanWindow()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void FillcanWindow::initWindow()
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    }

    bool FillcanWindow::shouldClose()
    {
        return glfwWindowShouldClose(window); 
    }
}