#include "vulkan/vulkan_core.h"
#include <fillcan/instance.hpp>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace fillcan {

static VKAPI_ATTR VkBool32 VKAPI_CALL
debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
              VkDebugUtilsMessageTypeFlagsEXT messageType,
              const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
              void *pUserData) {
  std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

  return VK_FALSE;
}

Instance::Instance(const char *pApplicationName,
                   unsigned int applicationVersion,
                   std::vector<const char *> requiredLayers,
                   std::vector<const char *> requiredExtensions) {
  if (!checkValidationLayerSupport({})) {
    throw std::runtime_error("Required validation layers are not available");
  }
  if (!checkExtensionSupport({})) {
    throw std::runtime_error("Required extensions are not supported");
  }

  VkApplicationInfo applicationInfo = {};
  applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  applicationInfo.pApplicationName = pApplicationName;
  applicationInfo.applicationVersion = applicationVersion;
  applicationInfo.pEngineName = "Fillcan";
  applicationInfo.engineVersion = 1.0;
  applicationInfo.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo instanceCreateInfo = {};
  instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  instanceCreateInfo.pApplicationInfo = &applicationInfo;
  instanceCreateInfo.enabledExtensionCount = requiredExtensions.size();
  instanceCreateInfo.ppEnabledExtensionNames = requiredExtensions.data();

#ifndef NDEBUG
  VkDebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCreateInfo = {};
  instanceCreateInfo.enabledLayerCount = requiredLayers.size();
  instanceCreateInfo.ppEnabledLayerNames = requiredLayers.data();

  debugUtilsMessengerCreateInfo.sType =
      VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  debugUtilsMessengerCreateInfo.messageSeverity =
      VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
      VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  debugUtilsMessengerCreateInfo.messageType =
      VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
      VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
      VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  debugUtilsMessengerCreateInfo.pfnUserCallback = debugCallback;
  debugUtilsMessengerCreateInfo.pUserData = nullptr;

  instanceCreateInfo.pNext = &debugUtilsMessengerCreateInfo;
#else
  instanceCreateInfo.enabledLayerCount = 0;
  instanceCreateInfo.ppEnabledLayerNames = nullptr;
#endif
  if (vkCreateInstance(&instanceCreateInfo, nullptr, &pInstance) !=
      VK_SUCCESS) {
    throw std::runtime_error("Failed to create instance");
  }
}

Instance::~Instance() {}

bool Instance::checkValidationLayerSupport(const char *layers) { return true; }
bool Instance::checkExtensionSupport(const char *extensions) { return true; }

} // namespace fillcan