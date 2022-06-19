
// fillcan
#include "vulkan/vulkan_core.h"
#include <fillcan/graphics/sampler.hpp>
#include <fillcan/instance/logical_device.hpp>

// std
#include <stdexcept>

namespace fillcan {
    Sampler::Sampler(LogicalDevice* pLogicalDevice, VkFilter magFilter, VkFilter minFilter, VkSamplerMipmapMode mipmapMode,
                     VkSamplerAddressMode addressModeU, VkSamplerAddressMode addressModeV, VkSamplerAddressMode addressModeW, float mipLodBias,
                     VkBool32 anisotropyEnable, float maxAnisotropy, VkBool32 compareEnable, VkCompareOp compareOp, float minLod, float maxLod,
                     VkBorderColor borderColor, VkBool32 unnormalizedCoordinates)
        : pLogicalDevice(pLogicalDevice) {

        if (this->pLogicalDevice == nullptr) {
            throw std::runtime_error("Failed to create sampler: Logical Device was NULL");
        }

        if (maxAnisotropy > this->pLogicalDevice->getPhysicalDevice()->getProperties().limits.maxSamplerAnisotropy) {
            throw std::runtime_error("Failed to create sampler: Requested max anisotropy is unsupported.");
        }
        VkSamplerCreateInfo samplerCreateInfo = {.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
                                                 .pNext = nullptr,
                                                 .flags = 0,
                                                 .magFilter = magFilter,
                                                 .minFilter = minFilter,
                                                 .mipmapMode = mipmapMode,
                                                 .addressModeU = addressModeU,
                                                 .addressModeV = addressModeV,
                                                 .addressModeW = addressModeW,
                                                 .mipLodBias = mipLodBias,
                                                 .anisotropyEnable = anisotropyEnable,
                                                 .maxAnisotropy = maxAnisotropy,
                                                 .compareEnable = compareEnable,
                                                 .compareOp = compareOp,
                                                 .minLod = minLod,
                                                 .maxLod = maxLod,
                                                 .borderColor = borderColor,
                                                 .unnormalizedCoordinates = unnormalizedCoordinates};

        if (vkCreateSampler(pLogicalDevice->getLogicalDeviceHandle(), &samplerCreateInfo, nullptr, &this->hSampler) != VK_SUCCESS) {
            throw "Failed to create sampler";
        }
    }
    Sampler::~Sampler() {
        if (this->pLogicalDevice == nullptr) {
            std::cerr << "Failed to destroy Sampler: Logical Device was NULL"
                      << "\n";
        }
        if (this->hSampler == VK_NULL_HANDLE) {
            std::cerr << "Failed to destroy Sampler: Handle was VK_NULL_HANDLE"
                      << "\n";
        }
        vkDestroySampler(this->pLogicalDevice->getLogicalDeviceHandle(), this->hSampler, nullptr);
    }

    VkSampler Sampler::getSamplerHandle() { return this->hSampler; }
} // namespace fillcan