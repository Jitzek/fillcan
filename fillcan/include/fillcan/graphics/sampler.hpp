#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

namespace fillcan {
    class LogicalDevice;
    class Sampler {
      private:
        VkSampler hSampler;
        LogicalDevice* pLogicalDevice;

      public:
        Sampler(LogicalDevice* pLogicalDevice, VkFilter magFilter, VkFilter minFilter, VkSamplerMipmapMode mipmapMode,
                VkSamplerAddressMode addressModeU, VkSamplerAddressMode addressModeV, VkSamplerAddressMode addressModeW, float mipLodBias,
                VkBool32 anisotropyEnable, float maxAnisotropy, VkBool32 compareEnable, VkCompareOp compareOp, float minLod, float maxLod,
                VkBorderColor borderColor, VkBool32 unnormalizedCoordinates);
        ~Sampler();

        Sampler(const Sampler&) = delete;
        Sampler& operator=(const Sampler&) = delete;

        VkSampler getSamplerHandle();
    };
} // namespace fillcan