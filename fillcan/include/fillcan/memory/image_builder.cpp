// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/memory/image.hpp>
#include <fillcan/memory/image_builder.hpp>
#include <memory>
#include <utility>

namespace fillcan {
    ImageBuilder::ImageBuilder() {}
    ImageBuilder::~ImageBuilder() {}

    void ImageBuilder::setLogicalDevice(LogicalDevice* pLogicalDevice) { this->pLogicalDevice = pLogicalDevice; }

    void ImageBuilder::setFlags(VkImageCreateFlags flags) { this->flags = flags; }

    void ImageBuilder::setImageType(VkImageType type) { this->type = type; }

    void ImageBuilder::setFormat(VkFormat format) { this->format = format; }

    void ImageBuilder::setExtent(VkExtent3D extent) { this->extent = extent; }

    void ImageBuilder::setMipLevels(unsigned int mipLevels) { this->mipLevels = mipLevels; }

    void ImageBuilder::setArrayLayers(unsigned int arrayLayers) { this->arrayLayers = arrayLayers; }

    void ImageBuilder::setSamples(VkSampleCountFlagBits samples) { this->samples = samples; }

    void ImageBuilder::setImageTiling(VkImageTiling tiling) { this->tiling = tiling; }

    void ImageBuilder::setImageUsage(VkImageUsageFlags usage) { this->usage = usage; }

    void ImageBuilder::setSharingMode(VkSharingMode sharingMode) { this->sharingMode = sharingMode; }

    void ImageBuilder::setQueueFamilyIndices(std::vector<uint32_t>& queueFamilyIndices) { this->queueFamilyIndices = queueFamilyIndices; }

    void ImageBuilder::setInitialLayout(VkImageLayout initialLayout) { this->initialLayout = initialLayout; }

    void ImageBuilder::reset() {
        this->pLogicalDevice = nullptr;
        this->flags = 0;
        this->type = VK_IMAGE_TYPE_2D;
        this->format = VK_FORMAT_R8G8B8A8_SRGB;
        this->extent = {1, 1, 1};
        this->mipLevels = 1;
        this->arrayLayers = 1;
        this->samples = VK_SAMPLE_COUNT_1_BIT;
        this->tiling = VK_IMAGE_TILING_OPTIMAL;
        this->usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT;
        this->sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        this->queueFamilyIndices.clear();
        this->initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    }

    std::unique_ptr<Image> ImageBuilder::getResult() {
        return std::move(std::make_unique<Image>(this->pLogicalDevice, this->flags, this->type, this->format, this->extent, this->mipLevels,
                                                 this->arrayLayers, this->samples, this->tiling, this->usage, this->sharingMode,
                                                 this->queueFamilyIndices, this->initialLayout));
    }
} // namespace fillcan