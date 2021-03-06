// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/memory/image.hpp>
#include <fillcan/memory/image_director.hpp>

// std
#include <memory>
#include <optional>
#include <vector>

namespace fillcan {
    ImageDirector::ImageDirector() : builder(ImageBuilder()) {}
    ImageDirector::~ImageDirector() {}

    std::unique_ptr<Image> ImageDirector::make2DTexture(LogicalDevice* pLogicalDevice, unsigned int width, unsigned int height,
                                                        VkSampleCountFlagBits samples, VkSharingMode sharingMode) {
        this->builder.reset();
        this->builder.setLogicalDevice(pLogicalDevice);
        this->builder.setFlags(0);
        this->builder.setImageType(VK_IMAGE_TYPE_2D);
        this->builder.setFormat(VK_FORMAT_R8G8B8A8_SRGB);
        this->builder.setExtent({width, height, 1});
        this->builder.setMipLevels(1);
        this->builder.setArrayLayers(1);
        this->builder.setSamples(samples);
        this->builder.setImageTiling(VK_IMAGE_TILING_OPTIMAL);
        this->builder.setImageUsage(VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT);
        this->builder.setSharingMode(sharingMode);
        this->builder.setInitialLayout(VK_IMAGE_LAYOUT_UNDEFINED);
        return std::move(this->builder.getResult());
    }

    std::unique_ptr<Image> ImageDirector::makeDepthImage(LogicalDevice* pLogicalDevice, unsigned int width, unsigned int height,
                                                         VkSampleCountFlagBits samples, VkSharingMode sharingMode) {
        this->builder.reset();
        this->builder.setLogicalDevice(pLogicalDevice);
        this->builder.setFlags(0);
        this->builder.setImageType(VK_IMAGE_TYPE_2D);
        std::optional<VkFormat> optFormat = pLogicalDevice->getPhysicalDevice()->findSupportedFormat(
            {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT}, VK_IMAGE_TILING_OPTIMAL,
            VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
        if (!optFormat.has_value()) {
            throw std::runtime_error("Failed to find a supported format");
        }
        this->builder.setFormat(optFormat.value());
        this->builder.setExtent({width, height, 1});
        this->builder.setMipLevels(1);
        this->builder.setArrayLayers(1);
        this->builder.setSamples(samples);
        this->builder.setImageTiling(VK_IMAGE_TILING_OPTIMAL);
        this->builder.setImageUsage(VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT);
        this->builder.setSharingMode(sharingMode);
        this->builder.setInitialLayout(VK_IMAGE_LAYOUT_UNDEFINED);
        return std::move(this->builder.getResult());
    }
} // namespace fillcan