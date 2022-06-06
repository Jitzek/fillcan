// vulkan
#include "vulkan/vulkan_core.h"

// std
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class Memory;

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

        void bindMemory(Memory* pMemory);
        const Memory* getMemory() const;
    };
} // namespace fillcan