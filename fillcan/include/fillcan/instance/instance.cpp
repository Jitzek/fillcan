// fillcan
#include <fillcan/instance/instance.hpp>

// std
#include <cstring>
#include <stdexcept>

namespace fillcan {
    // Local callbacks
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                        VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
        std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
        return VK_FALSE;
    }

    // ENDOF local callbacks

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

#ifndef NDEBUG
        instanceCreateInfo.enabledLayerCount = this->requiredLayers.size();
        instanceCreateInfo.ppEnabledLayerNames = this->requiredLayers.data();

        VkDebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCreateInfo = {};
        debugUtilsMessengerCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        debugUtilsMessengerCreateInfo.messageSeverity =
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        debugUtilsMessengerCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                                    VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        debugUtilsMessengerCreateInfo.pfnUserCallback = debugCallback;
        debugUtilsMessengerCreateInfo.pUserData = nullptr;

        instanceCreateInfo.pNext = &debugUtilsMessengerCreateInfo;
#else
        instanceCreateInfo.enabledLayerCount = 0;
        instanceCreateInfo.ppEnabledLayerNames = nullptr;
#endif

        if (vkCreateInstance(&instanceCreateInfo, nullptr, &this->hInstance) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create instance");
        }

#ifndef NDEBUG
        auto func = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(this->hInstance, "vkCreateDebugUtilsMessengerEXT"));
        if (func == nullptr) {
            throw std::runtime_error("Failed to set up debug messenger");
        }
        if (func(this->hInstance, &debugUtilsMessengerCreateInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
            throw std::runtime_error("Failed to set up debug messenger");
        }
#endif
    }

    Instance::~Instance() {
#ifndef NDEBUG
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(this->hInstance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr) {
            func(this->hInstance, debugMessenger, nullptr);
        }
#endif
        if (this->hInstance == VK_NULL_HANDLE) {
            std::cerr << "Failed to destroy Instance: Handle was VK_NULL_HANDLE"
                      << "\n";
        }
        vkDestroyInstance(this->hInstance, nullptr);
    }

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
    bool Instance::checkExtensionSupport(std::vector<const char*> extensions) { /* TODO: */ return true; }

    VkInstance Instance::getInstanceHandle() const { return this->hInstance; }

} // namespace fillcan