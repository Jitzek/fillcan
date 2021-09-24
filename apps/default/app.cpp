#include "app.hpp"

// std
#include <iostream>

namespace app
{
    App::App() {}
    App::~App() {}

    void App::run()
    {
        std::cout << "Running App \"Default\"" << std::endl;

        while(!window.shouldClose()) {
            glfwPollEvents();
        }
    }
}