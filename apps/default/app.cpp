// vulkan
#include "vulkan/vulkan_core.h"

#include "app.hpp"

// std
#include <iostream>
#include <memory>
#include <thread>

namespace app {
    App::App() {
    }
    App::~App() {}

    void App::run() {
        std::string name = "Default Application";
        std::cout << "Running App \"" << name << "\"\n";
        upFillcan = std::make_unique<fillcan::Fillcan>(name.c_str(), 1.0, 800, 600, (VkPhysicalDeviceFeatures){.samplerAnisotropy = true});

        // Select any device
        upFillcan->selectDevice(0);

        upFillcan->MainLoop(std::bind(&App::update, this));
    }

    void App::update() {}
} // namespace app