#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// std
#include <vector>

namespace fillcan {
class Instance {
private:
  VkInstance pInstance;

  bool checkValidationLayerSupport(const char *layers);
  bool checkExtensionSupport(const char *extensions);

public:
  Instance(const char *pApplicationName, unsigned int applicationVersion,
            std::vector<const char*> requiredLayers, std::vector<const char*> requiredExtensions);
  ~Instance();
  Instance(const Instance &) = delete;
  Instance &operator=(const Instance &) = delete;
};
} // namespace fillcan