
// fillcan
#include <fillcan/fillcan.hpp>
#include <fillcan/instance/logical_device.hpp>

// std
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

namespace fillcan {

    std::vector<const char*> requiredInstanceLayers = {
#ifndef NDEBUG
        "VK_LAYER_KHRONOS_validation"
#endif
    };

    std::vector<const char*> requiredInstanceExtensions = {
#ifndef NDEBUG
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME
#endif
    };

    std::vector<const char*> requiredDeviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

    Fillcan::Fillcan(const char* pApplicationName, uint32_t applicationVersion, unsigned int windowWidth, unsigned int windowHeight,
                     VkPhysicalDeviceFeatures requiredDeviceFeatures) {
        // Initialize Window
        this->upWindow = std::make_unique<Window>(windowWidth, windowHeight, pApplicationName);

        // Initialize Instance
        std::vector<const char*> windowExtensions = upWindow->getRequiredExtensions();
        requiredInstanceExtensions.insert(requiredInstanceExtensions.begin(), windowExtensions.begin(), windowExtensions.end());
        this->upInstance = std::make_unique<Instance>(pApplicationName, applicationVersion, requiredInstanceLayers, requiredInstanceExtensions);

        // Create surface of Window using Instance
        this->upWindow->createSurface(this->upInstance.get());

        // Initialize Device Pool
        this->upDevicePool =
            std::make_unique<DevicePool>(this->upInstance.get(), this->upWindow.get(), requiredDeviceExtensions, requiredDeviceFeatures);
    }

    Fillcan::~Fillcan() {}

    void Fillcan::MainLoop(std::function<void()> callback) {
        while (!upWindow->shouldClose()) {
            glfwPollEvents();

            callback();
        }
    }

    const std::vector<PhysicalDevice> Fillcan::getSupportedPhysicalDevices() const { return this->upDevicePool->getSupportedPhysicalDevices(); }

    LogicalDevice* Fillcan::selectDevice(unsigned int deviceIndex) { return this->upDevicePool->selectDevice(deviceIndex); }

    LogicalDevice* Fillcan::getCurrentDevice() { return this->upDevicePool->getCurrentDevice(); }

    Swapchain* Fillcan::createSwapchain(BufferMode bufferMode, VkPresentModeKHR presentMode) {
        this->upSwapchain = std::make_unique<Swapchain>(this->getCurrentDevice(), this->upWindow.get(), bufferMode, presentMode, nullptr);
        return this->upSwapchain.get();
    }

    Swapchain* Fillcan::recreateSwapchain(BufferMode bufferMode, VkPresentModeKHR presentMode) {
        if (this->upSwapchain == nullptr) {
            return nullptr;
        }
        this->upSwapchain =
            std::make_unique<Swapchain>(this->getCurrentDevice(), this->upWindow.get(), bufferMode, presentMode, this->upSwapchain.get());
        return this->upSwapchain.get();
    }
} // namespace fillcan