#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// std
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

namespace fillcan {
    class Instance {
      private:
        VkInstance hInstance;
        std::string applicationName;
        unsigned int applicationVersion;
        std::vector<const char*> requiredLayers;
        std::vector<const char*> requiredExtensions;
        VkDebugUtilsMessengerEXT debugMessenger;

        bool checkValidationLayerSupport(std::vector<const char*> layers);
        bool checkExtensionSupport(std::vector<const char*> extensions);

      public:
        Instance(std::string pApplicationName, unsigned int applicationVersion, std::vector<const char*> requiredLayers,
                 std::vector<const char*> requiredExtensions);
        ~Instance();
        
        Instance(const Instance&) = delete;
        Instance& operator=(const Instance&) = delete;

        VkInstance getInstanceHandle() const;
    };
} // namespace fillcan