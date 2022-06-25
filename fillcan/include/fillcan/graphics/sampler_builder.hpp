#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// std
#include <memory>

namespace fillcan {
    class LogicalDevice;
    class Sampler;
    class SamplerBuilder {
      private:
        LogicalDevice* pLogicalDevice = nullptr;
        VkFilter magFilter = VK_FILTER_LINEAR;
        VkFilter minFilter = VK_FILTER_LINEAR;
        VkSamplerMipmapMode mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
        VkSamplerAddressMode addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        VkSamplerAddressMode addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        VkSamplerAddressMode addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        float mipLodBias = 0.f;
        VkBool32 anisotropyEnable = VK_FALSE;
        float maxAnisotropy = 1.0f;
        VkBool32 compareEnable = VK_FALSE;
        VkCompareOp compareOp = VK_COMPARE_OP_ALWAYS;
        float minLod = 0.f;
        float maxLod = 0.f;
        VkBorderColor borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
        VkBool32 unnormalizedCoordinates = VK_FALSE;

      public:
        SamplerBuilder();
        ~SamplerBuilder();

        void setLogicalDevice(LogicalDevice* pLogicalDevice);
        void setFilters(VkFilter magFilter, VkFilter minFilter);
        void setMipmapMode(VkSamplerMipmapMode mipmapMode);
        void setAddressModes(VkSamplerAddressMode addressModeU, VkSamplerAddressMode addressModeV, VkSamplerAddressMode addressModeW);
        void setMipLodBias(float mipLodBias);
        void setMaxAnisotropy(float maxAnisotropy);
        void unsetMaxAnisotropy();
        void setCompareOp(VkCompareOp compareOp);
        void unsetCompareOp();
        void setLod(float minLod, float maxLod);
        void setBorderColor(VkBorderColor borderColor);
        void enableUnnormalizedCoordinates();
        void disableUnnormalizedCoordinates();

        void reset();
        std::unique_ptr<Sampler> getResult();
    };
} // namespace fillcan