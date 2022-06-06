// vulkan
#include "vulkan/vulkan_core.h"

// std
#include <memory>
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class Memory;
    class ImageView;

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
        std::vector<std::unique_ptr<ImageView>> imageViews;

      public:
        Image(LogicalDevice* pLogicalDevice, VkImageCreateFlags flags, VkImageType type, VkFormat format, VkExtent3D extent, unsigned int mipLevels,
              unsigned int arrayLayers, VkSampleCountFlagBits samples, VkImageTiling tiling, VkImageUsageFlags usage, VkSharingMode sharingMode,
              std::vector<uint32_t>& queueFamilyIndices, VkImageLayout initialLayout);
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
                                   VkImageSubresourceRange subresourceRange = {.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                                                                               .baseMipLevel = 0,
                                                                               .levelCount = 1,
                                                                               .baseArrayLayer = 0,
                                                                               .layerCount = 1},
                                   VkComponentMapping components = {.r = VK_COMPONENT_SWIZZLE_IDENTITY,
                                                                    .g = VK_COMPONENT_SWIZZLE_IDENTITY,
                                                                    .b = VK_COMPONENT_SWIZZLE_IDENTITY,
                                                                    .a = VK_COMPONENT_SWIZZLE_IDENTITY});
        const std::vector<std::unique_ptr<ImageView>>& getImageViews() const;
    };
} // namespace fillcan