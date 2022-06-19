#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/memory/image_view.hpp>

// std
#include <memory>
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class Memory;
    class Swapchain;
    class CommandBuffer;
    class Buffer;

    class Image {
      private:
        VkImage hImage;
        LogicalDevice* pLogicalDevice;
        VkImageCreateFlags flags;
        VkImageType type;
        VkFormat format;
        VkExtent3D extent;
        unsigned int mipLevels;
        unsigned int arrayLayers;
        VkSampleCountFlagBits samples;
        VkImageTiling tiling;
        VkImageUsageFlags usage;
        VkSharingMode sharingMode;
        std::vector<uint32_t> queueFamilyIndices;
        VkImageLayout initialLayout;
        Memory* pMemory;
        std::vector<std::unique_ptr<ImageView>> upImageViews;
        bool isSwapchainImage = false;

      public:
        Image(LogicalDevice* pLogicalDevice, VkImageCreateFlags flags, VkImageType type, VkFormat format, VkExtent3D extent, unsigned int mipLevels,
              unsigned int arrayLayers, VkSampleCountFlagBits samples, VkImageTiling tiling, VkImageUsageFlags usage, VkSharingMode sharingMode,
              std::vector<uint32_t>& queueFamilyIndices, VkImageLayout initialLayout);
        Image(LogicalDevice* pLogicalDevice, Swapchain* pSwapchain, VkImage hImage);
        ~Image();

        VkImage getImageHandle();

        VkImageCreateFlags getFlags();
        VkImageType getType();
        VkFormat getFormat();
        VkExtent3D getExtent();
        unsigned int getMipLevels();
        unsigned int getArrayLayers();
        VkSampleCountFlagBits getSamples();
        VkImageTiling getTiling();
        VkImageUsageFlags getUsage();
        VkSharingMode getSharingMode();
        const std::vector<uint32_t>& getQueueFamilyIndices() const;
        VkImageLayout getInitialLayout();

        void bindMemory(Memory* pMemory, VkDeviceSize memoryOffset = 0);
        const Memory* getMemory() const;

        ImageView* createImageView(VkImageViewType viewType, VkFormat format,
                                   VkImageSubresourceRange subresourceRange = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1},
                                   VkComponentMapping components = {VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY,
                                                                    VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY});
        std::vector<ImageView*> getImageViews();
        void destroyImageViews();

        void copyTo(CommandBuffer* pCommandBuffer, Image* pImage, VkImageLayout srcLayout, VkImageLayout dstLayout,
                    std::vector<VkImageCopy>& regions);
        void copyTo(CommandBuffer* pCommandBuffer, Buffer* pBuffer, VkImageLayout srcLayout, std::vector<VkBufferImageCopy>& regions);
    };
} // namespace fillcan