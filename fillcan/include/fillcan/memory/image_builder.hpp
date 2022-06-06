// vulkan
#include "vulkan/vulkan_core.h"

// std
#include <vector>
#include <memory>

namespace fillcan {
    class LogicalDevice;
    class Image;
    class ImageBuilder {
      private:
        LogicalDevice* pLogicalDevice = nullptr;
        VkImageCreateFlags flags = 0;
        VkImageType type = VK_IMAGE_TYPE_2D;
        VkFormat format = VK_FORMAT_R8G8B8A8_SRGB;
        VkExtent3D extent = {1, 1, 1};
        unsigned int mipLevels = 1;
        unsigned int arrayLayers = 1;
        VkSampleCountFlagBits samples = VK_SAMPLE_COUNT_1_BIT;
        VkImageTiling tiling = VK_IMAGE_TILING_OPTIMAL;
        VkImageUsageFlags usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT;
        VkSharingMode sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        std::vector<uint32_t> queueFamilyIndices = {};
        VkImageLayout initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

      public:
        ImageBuilder();
        ~ImageBuilder();

        void setLogicalDevice(LogicalDevice* pLogicalDevice);
        void setFlags(VkImageCreateFlags flags);
        void setImageType(VkImageType type);
        void setFormat(VkFormat format);
        void setExtent(VkExtent3D extent);
        void setMipLevels(unsigned int mipLevels);
        void setArrayLayers(unsigned int arrayLayers);
        void setSamples(VkSampleCountFlagBits samples);
        void setImageTiling(VkImageTiling tiling);
        void setImageUsage(VkImageUsageFlags usage);
        void setSharingMode(VkSharingMode sharingMode);
        void setQueueFamilyIndices(std::vector<uint32_t>& queueFamilyIndices);
        void setInitialLayout(VkImageLayout initialLayout);

        void reset();
        std::unique_ptr<Image> getResult();
    };
} // namespace fillcan