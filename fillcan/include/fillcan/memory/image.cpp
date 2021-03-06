// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/graphics/swapchain.hpp>
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/memory/buffer.hpp>
#include <fillcan/memory/image.hpp>
#include <fillcan/memory/image_view.hpp>
#include <fillcan/memory/memory.hpp>

// std
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <vector>

namespace fillcan {
    Image::Image(LogicalDevice* pLogicalDevice, VkImageCreateFlags flags, VkImageType type, VkFormat format, VkExtent3D extent,
                 unsigned int mipLevels, unsigned int arrayLayers, VkSampleCountFlagBits samples, VkImageTiling tiling, VkImageUsageFlags usage,
                 VkSharingMode sharingMode, std::vector<uint32_t>& queueFamilyIndices, VkImageLayout initialLayout)
        : pLogicalDevice(pLogicalDevice), flags(flags), type(type), format(format), extent(extent), mipLevels(mipLevels), arrayLayers(arrayLayers),
          samples(samples), tiling(tiling), usage(usage), sharingMode(sharingMode), queueFamilyIndices(queueFamilyIndices),
          initialLayout(initialLayout), upImageViews(std::vector<std::unique_ptr<ImageView>>()) {
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

    Image::Image(LogicalDevice* pLogicalDevice, Swapchain* pSwapchain, VkImage hImage)
        : pLogicalDevice(pLogicalDevice), hImage(hImage), flags(0), type(VK_IMAGE_TYPE_2D), format(pSwapchain->getSurfaceFormat().format),
          extent({.width = pSwapchain->getImageExtent().width, .height = pSwapchain->getImageExtent().height, .depth = 1}), mipLevels(1),
          arrayLayers(pSwapchain->getImageArrayLayers()), samples(VK_SAMPLE_COUNT_FLAG_BITS_MAX_ENUM), tiling(VK_IMAGE_TILING_MAX_ENUM),
          usage(pSwapchain->getImageUsage()), sharingMode(pSwapchain->getImageSharingMode()), queueFamilyIndices(pSwapchain->getQueueFamilyIndices()),
          initialLayout(VK_IMAGE_LAYOUT_UNDEFINED), upImageViews(std::vector<std::unique_ptr<ImageView>>()) {
        this->isSwapchainImage = true;
    }

    Image::~Image() {
        if (this->isSwapchainImage) {
            // Swapchain handles destruction of image handles
            return;
        }
        if (this->pLogicalDevice == nullptr) {
            std::cerr << "Failed to destroy Image: Logical Device was NULL"
                      << "\n";
        }
        if (this->hImage == VK_NULL_HANDLE) {
            std::cerr << "Failed to destroy Image: Handle was VK_NULL_HANDLE"
                      << "\n";
        }
        vkDestroyImage(this->pLogicalDevice->getLogicalDeviceHandle(), this->hImage, nullptr);
    }

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

    unsigned int Image::createImageView(VkImageViewType viewType, VkFormat format, VkImageSubresourceRange subresourceRange,
                                        VkComponentMapping components) {
        this->upImageViews.emplace_back(
            std::move(std::make_unique<ImageView>(this->pLogicalDevice, this, viewType, format, subresourceRange, components)));
        return this->upImageViews.size() - 1;
    }

    std::vector<ImageView*> Image::getImageViews() {
        std::vector<ImageView*> pImageViews = {};
        pImageViews.reserve(this->upImageViews.size());
        std::transform(this->upImageViews.begin(), this->upImageViews.end(), std::back_inserter(pImageViews),
                       [](const std::unique_ptr<ImageView>& upImageView) { return upImageView.get(); });
        return pImageViews;
    }

    ImageView* Image::getImageView(unsigned int index) { return this->upImageViews.at(index).get(); }

    void Image::destroyImageView(unsigned int index) { this->upImageViews.erase(this->upImageViews.begin() + index); }

    void Image::destroyImageViews() { this->upImageViews.clear(); }

    void Image::copyTo(CommandBuffer* pCommandBuffer, Image* pImage, VkImageLayout srcLayout, VkImageLayout dstLayout,
                       std::vector<VkImageCopy>& regions) {
        vkCmdCopyImage(pCommandBuffer->getCommandBufferHandle(), this->hImage, srcLayout, pImage->getImageHandle(), dstLayout,
                       static_cast<uint32_t>(regions.size()), regions.data());
    }

    void Image::copyTo(CommandBuffer* pCommandBuffer, Buffer* pBuffer, VkImageLayout srcLayout, std::vector<VkBufferImageCopy>& regions) {
        vkCmdCopyImageToBuffer(pCommandBuffer->getCommandBufferHandle(), this->hImage, srcLayout, pBuffer->getBufferHandle(),
                               static_cast<uint32_t>(regions.size()), regions.data());
    }

    void Image::transitionImageLayout(CommandBuffer* pCommandBuffer, VkImageLayout oldLayout, VkImageLayout newLayout, VkAccessFlags srcAccessMask,
                                      VkAccessFlags dstAccessMask, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask,
                                      VkDependencyFlags dependencyFlags) {
        VkImageMemoryBarrier barrier{.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
                                     .pNext = nullptr,
                                     .srcAccessMask = srcAccessMask,
                                     .dstAccessMask = dstAccessMask,
                                     .oldLayout = oldLayout,
                                     .newLayout = newLayout,
                                     .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
                                     .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
                                     .image = this->hImage,
                                     .subresourceRange = {.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                                                          .baseMipLevel = 0,
                                                          .levelCount = this->mipLevels,
                                                          .baseArrayLayer = 0,
                                                          .layerCount = this->arrayLayers}};
        vkCmdPipelineBarrier(pCommandBuffer->getCommandBufferHandle(), srcStageMask, dstStageMask, dependencyFlags, 0, nullptr, 0, nullptr, 1,
                             &barrier);
    }

} // namespace fillcan