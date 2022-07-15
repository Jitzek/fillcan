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
        /**
         * @brief Create a new Image.
         *
         * @param pLogicalDevice A pointer to the Logical Device the Image should be associated with.
         * @param flags A bitmask of VkImageCreateFlagBits hat describe some properties of the image.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageCreateFlagBits.html
         * @param type The type of image being created. The image type is essentially the dimensionality of the image and can be VK_IMAGE_TYPE_1D,
         * VK_IMAGE_TYPE_2D or VK_IMAGE_TYPE_3D for a 1D, 2D or 3D image respectively.
         * @param format Describes how texel data is stored in memory and interpreted by Vulkan.
         * @param extent The size of the image in texels. This should be an instance of the VkExtent3D structure , which has three members: width,
         * height, and depth. These should be set respectively to the width, height and depth of the desired image. For 1D images, the height should
         * be set to 1, and for 1D and 2D images, the depth should be set to 1.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkExtent3D.html
         * @param mipLevels The number of mipmap levels to create in the image.
         * @param arrayLayers The amount of images each mipmap level of the image has.
         * @param samples The number of samples in the image. It must be a member of the VkSampleCountFlagBits-Enumerant.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSampleCountFlagBits.html
         * @param tiling A member of the VkImageTiling enumerant, which contains only VK_IMAGE_TILING_LINEAR or VK_IMAGE_TILING_OPTIMAL. Linear tiling
         * means that image data is laid out from left to right, top to bottom, so that if the underlying memory is mapped and it is written with the
         * CPU, it would form a linear image. Meanwhile, optimal tiling is an opaque display used by Vulkan to store data in memory to improve the
         * efficiency of the memory subsystem on the device. This is generally what should be chosen unless the image needs to be CPU mapped and
         * manipulated. Optimal tiling is likely to outperform linear tiling in most operations, and linear tiling may not be supported at all for
         * some operations or formats, depending on the Vulkan implementation.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageTiling.html
         * @param usage A bitmask describing the intended usage for the image consisting of members of the VkImageUsageFlagBits-enumerant.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageUsageFlagBits.html
         * @param sharingMode A member of the VkSharingMode-enumerant indicating how the image will be used in the multiple device queues supported
         * by the device. Because Vulkan can run many commands in parallel, some implementations need to know whether the image will essentially be
         * used by a single command at a time or possibly by several. Setting sharingMode to VK_SHARING_MODE_EXCLUSIVE tell Vulkan that the image
         * will only be used for a single queue, while setting sharingMode to VK_SHARING_MODE_CONCURRENT specifies that the application will use the
         * image on multiple queues at once. Using VK_SHARING_MODE_CONCURRENT may result in lower performance on some systems, so unless necessary,
         * sharingMode should be set to VK_SHARING_MODE_EXCLUSIVE.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSharingMode.html
         * @param queueFamilyIndices An array of queue family indices on which the buffer will be used.
         * @param initialLayout Images have a layout, which partially indicates how they will be used at a given time. This field determines the
         * layout in which the image is created. The available layouts are the members of the VkImageLayout enumerant.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageLayout.html
         * Images should initially be created in the format VK_IMAGE_LAYOUT_UNDEFINED or VK_IMAGE_LAYOUT_PREINITIALIZED.
         * VK_IMAGE_LAYOUT_PREINITIALIZED should only be used if there is data in memory that is bound immediately to the image source.
         * VK_IMAGE_LAYOUT_UNDEFINED should be used when moving the resource to another layout before use. Images can be moved out of the
         * VK_IMAGE_LAYOUT_UNDEFINED layout at any time with little or no time cost.
         */
        Image(LogicalDevice* pLogicalDevice, VkImageCreateFlags flags, VkImageType type, VkFormat format, VkExtent3D extent, unsigned int mipLevels,
              unsigned int arrayLayers, VkSampleCountFlagBits samples, VkImageTiling tiling, VkImageUsageFlags usage, VkSharingMode sharingMode,
              std::vector<uint32_t>& queueFamilyIndices, VkImageLayout initialLayout);
        Image(LogicalDevice* pLogicalDevice, Swapchain* pSwapchain, VkImage hImage);
        ~Image();

        Image(const Image&) = delete;
        Image& operator=(const Image&) = delete;

        VkImage getImageHandle();

        VkImageCreateFlags getFlags();

        VkImageUsageFlags getUsage();

        VkSharingMode getSharingMode();

        const std::vector<uint32_t>& getQueueFamilyIndices() const;

        VkImageType getType();

        VkFormat getFormat();

        VkExtent3D getExtent();

        unsigned int getMipLevels();

        unsigned int getArrayLayers();

        VkSampleCountFlagBits getSamples();

        VkImageTiling getTiling();

        VkImageLayout getInitialLayout();

        void bindMemory(Memory* pMemory, VkDeviceSize memoryOffset = 0);

        const Memory* getMemory() const;

        unsigned int createImageView(VkImageViewType viewType, VkFormat format,
                                     VkImageSubresourceRange subresourceRange = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1},
                                     VkComponentMapping components = {VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY,
                                                                      VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY});

        std::vector<ImageView*> getImageViews();

        ImageView* getImageView(unsigned int index);

        void destroyImageViews();

        void destroyImageView(unsigned int index);

        void copyTo(CommandBuffer* pCommandBuffer, Image* pImage, VkImageLayout srcLayout, VkImageLayout dstLayout,
                    std::vector<VkImageCopy>& regions);

        void copyTo(CommandBuffer* pCommandBuffer, Buffer* pBuffer, VkImageLayout srcLayout, std::vector<VkBufferImageCopy>& regions);

        void transitionImageLayout(CommandBuffer* pCommandBuffer, VkImageLayout oldLayout, VkImageLayout newLayout, VkAccessFlags srcAccessMask,
                                   VkAccessFlags dstAccessMask, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask,
                                   VkDependencyFlags dependencyFlags = 0);
    };
} // namespace fillcan