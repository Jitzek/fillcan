// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/memory/image.hpp>
#include <fillcan/memory/image_view.hpp>
#include <fillcan/memory/memory.hpp>

// std
#include <stdexcept>
#include <vector>

namespace fillcan {
    Image::Image(LogicalDevice* pLogicalDevice, VkImageCreateFlags flags, VkImageType type, VkFormat format, VkExtent3D extent,
                 unsigned int mipLevels, unsigned int arrayLayers, VkSampleCountFlagBits samples, VkImageTiling tiling, VkImageUsageFlags usage,
                 VkSharingMode sharingMode, std::vector<uint32_t>& queueFamilyIndices, VkImageLayout initialLayout)
        : pLogicalDevice(pLogicalDevice), flags(flags), type(type), format(format), extent(extent), mipLevels(mipLevels), arrayLayers(arrayLayers),
          samples(samples), tiling(tiling), usage(usage), sharingMode(sharingMode), queueFamilyIndices(queueFamilyIndices),
          initialLayout(initialLayout), imageViews((std::vector<std::unique_ptr<ImageView>>){}) {
        VkImageCreateInfo imageCreateInfo = {};
        imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageCreateInfo.pNext = nullptr;
        imageCreateInfo.flags = this->flags;
        imageCreateInfo.imageType = this->type;
        imageCreateInfo.format = this->format;
        imageCreateInfo.extent = this->extent;
        imageCreateInfo.mipLevels = this->mipLevels;
        imageCreateInfo.arrayLayers = this->arrayLayers;
        imageCreateInfo.samples = this->samples;
        imageCreateInfo.tiling = this->tiling;
        imageCreateInfo.usage = this->usage;
        imageCreateInfo.sharingMode = this->sharingMode;
        if (this->sharingMode == VK_SHARING_MODE_CONCURRENT) {
            imageCreateInfo.queueFamilyIndexCount = static_cast<uint32_t>(this->queueFamilyIndices.size());
            imageCreateInfo.pQueueFamilyIndices = queueFamilyIndices.data();
        }
        imageCreateInfo.initialLayout = this->initialLayout;
        if (vkCreateImage(this->pLogicalDevice->getLogicalDeviceHandle(), &imageCreateInfo, nullptr, &this->hImage) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create image");
        }
    }
    Image::~Image() {}

    VkImage Image::getImageHandle() { return this->hImage; }

    VkImageCreateFlags Image::getFlags() { return this->flags; }

    VkImageType Image::getType() { return this->type; }

    VkFormat Image::getFormat() { return this->format; }

    VkExtent3D Image::getExtent() { return this->extent; }

    unsigned int Image::getMipLevels() { return this->mipLevels; }

    unsigned int Image::getArrayLayers() { return this->arrayLayers; }

    VkSampleCountFlagBits Image::getSamples() { return this->samples; }

    VkImageTiling Image::getTiling() { return this->tiling; }

    VkImageUsageFlags Image::getUsage() { return this->usage; }

    VkSharingMode Image::getSharingMode() { return this->sharingMode; }

    const std::vector<uint32_t>& Image::getQueueFamilyIndices() const { return this->queueFamilyIndices; }

    VkImageLayout Image::getInitialLayout() { return this->initialLayout; }

    void Image::bindMemory(Memory* pMemory, VkDeviceSize memoryOffset) {
        if (vkBindImageMemory(this->pLogicalDevice->getLogicalDeviceHandle(), this->hImage, pMemory->getMemoryHandle(), memoryOffset) != VK_SUCCESS) {
            throw std::runtime_error("Failed to bind memory to image");
        }
        this->pMemory = pMemory;
    }

    const Memory* Image::getMemory() const { return this->pMemory; }

    ImageView* Image::createImageView(VkImageViewType viewType, VkFormat format, VkImageSubresourceRange subresourceRange,
                                      VkComponentMapping components) {
        // TODO: validate if given format is allowed for this image
        // VkFormatProperties formatProperties;
        // vkGetPhysicalDeviceFormatProperties(this->pLogicalDevice->getPhysicalDevice()->getPhysicalDeviceHandle(), format, &formatProperties);

        this->imageViews.emplace_back(std::make_unique<ImageView>(this->pLogicalDevice, this, viewType, format, subresourceRange, components));
        return this->imageViews.back().get();
    }
    const std::vector<std::unique_ptr<ImageView>>& Image::getImageViews() const { return this->imageViews; }
} // namespace fillcan