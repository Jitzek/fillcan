#include "app.hpp"

// std
#include <iostream>
#include <thread>

namespace app
{
    App::App() {}
    App::~App() {}

    void App::run()
    {
        std::cout << "Running App \"Default\"" << std::endl;

        fillcan.MainLoop(std::bind(&App::update, this));
    }

    void App::update()
    {
        
    }
}