// vulkan
#include "fillcan/commands/command_recording.hpp"
#include "vulkan/vulkan_core.h"

#include "app.hpp"

// fillcan
#include <fillcan/commands/queue.hpp>

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
        fillcan::LogicalDevice* currentDevice = upFillcan->selectDevice(0);

        fillcan::CommandRecording graphicsRecording = currentDevice->getGraphicsQueue()->createRecording(2, 1);
        fillcan::CommandRecording graphicsRecording2 = currentDevice->getGraphicsQueue()->createRecording(1, 1);
        fillcan::CommandRecording presentRecording = currentDevice->getPresentQueue()->createRecording(2, 1);
        fillcan::CommandRecording computRecording = currentDevice->getComputeQueue()->createRecording(2, 1);

        currentDevice->getGraphicsQueue()->submitRecordings({&graphicsRecording}, nullptr);
        // currentDevice->getGraphicsQueue()->freeRecording(graphicsRecording);

        upFillcan->MainLoop(std::bind(&App::update, this));
    }

    void App::update() {}
} // namespace app