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
        /**
         * @brief Create a new Instance.
         *
         * @details The Instance class is the connection between the application and the Vulkan library and to create it some details of the
         * application need to be specified to the driver. The instance contains information such as an application name, name and version of the
         * engine used to create the application, and enabled instance-level extensions and layers.
         * Vulkan can be seen as a subsystem of the application. Once the application is linked to the Vulkan libraries and initialized, a certain
         * state is tracked. Vulkan does not introduce a global state in the application, so all tracked state must be stored in an object that the
         * application provides, the Instance class.
         *
         * @param pApplicationName The name of the application.
         * @param applicationVersion The version of the application.
         * @param requiredLayers The Instance layers that should be enabled. To get a list of supported layers the function
         * vkEnumerateInstanceLayerProperties() can be called
         * ( @see https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/vkEnumerateInstanceLayerProperties.html ).
         * @param requiredExtensions The Instance extensions that should be enabled. To get a list of supported extensions the function
         * vkEnumerateInstanceExtensionProperties() can be called
         * ( @see https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/vkEnumerateInstanceExtensionProperties.html ).
         */
        Instance(std::string pApplicationName, unsigned int applicationVersion, std::vector<const char*> requiredLayers,
                 std::vector<const char*> requiredExtensions);
        ~Instance();
        Instance(const Instance&) = delete;
        Instance& operator=(const Instance&) = delete;

        /**
         * @brief Get the handle to the Vulkan Instance.
         *
         * @return The handle to the Vulkan Instance.
         */
        const VkInstance getInstanceHandle() const;
    };
} // namespace fillcan