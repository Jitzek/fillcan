// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <cstddef>
#include <fillcan/instance.hpp>

// std
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace fillcan {

    Instance::Instance(std::string applicationName, unsigned int applicationVersion, std::vector<const char*> requiredLayers,
                       std::vector<const char*> requiredExtensions)
        : applicationName(applicationName), applicationVersion(applicationVersion), requiredLayers(requiredLayers),
          requiredExtensions(requiredExtensions) {
        if (!checkValidationLayerSupport(this->requiredLayers)) {
            throw std::runtime_error("Required validation layers are not available");
        }
        if (!checkExtensionSupport(this->requiredExtensions)) {
            throw std::runtime_error("Required extensions are not supported");
        }

        VkApplicationInfo applicationInfo = {};
        applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        applicationInfo.pApplicationName = this->applicationName.c_str();
        applicationInfo.applicationVersion = applicationVersion;
        applicationInfo.pEngineName = "Fillcan";
        applicationInfo.engineVersion = 1.0;
        applicationInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo instanceCreateInfo = {};
        instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceCreateInfo.pApplicationInfo = &applicationInfo;
        instanceCreateInfo.enabledExtensionCount = this->requiredExtensions.size();
        instanceCreateInfo.ppEnabledExtensionNames = this->requiredExtensions.data();

        instanceCreateInfo.enabledLayerCount = this->requiredLayers.size();
        instanceCreateInfo.ppEnabledLayerNames = this->requiredLayers.data();

        if (vkCreateInstance(&instanceCreateInfo, nullptr, &this->hInstance) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create instance");
        }
    }

    Instance::~Instance() {}

    bool Instance::checkValidationLayerSupport(std::vector<const char*> layers) {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (const char* layerName : layers) {
            bool layerFound = false;
            for (const VkLayerProperties& layerProperties : availableLayers) {
                if (strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound) {
                return false;
            }
        }

        return true;
    }
    bool Instance::checkExtensionSupport(std::vector<const char*> extensions) { return true; }

    VkInstance Instance::getInstance() { return this->hInstance; }

} // namespace fillcan