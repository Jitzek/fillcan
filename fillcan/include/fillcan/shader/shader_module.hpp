#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan

// std

namespace fillcan {
    class ShaderModule {
      private:
        VkShaderModule hShaderModule;
      public:
        ShaderModule();
        ~ShaderModule();

        VkShaderModule getShaderModuleHandle();
    };
} // namespace fillcan