#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// std
#include <memory>
#include <vector>

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
        /**
         * @brief Create a new Image Builder.
         *
         * @details The Image Builder class is part of the creational design pattern to construct complex objects step by step.
         * The Builder pattern allows you to produce different types and representations of an object using the same construction code.
         *
         * @note It is recommended to use the Image Director for creating Images unless the director doesn't offer the required configuration.
         */
        ImageBuilder();

        ~ImageBuilder();

        /**
         * @brief Set the Logical Device for the Image.
         *
         * @param pLogicalDevice A pointer to the Logical Device the Image should be associated with.
         */
        void setLogicalDevice(LogicalDevice* pLogicalDevice);

        /**
         * @brief Set the flags for the Buffer.
         *
         * @param flags A bitmask of VkImageCreateFlagBits that describe some properties of the image.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageCreateFlagBits.html
         */
        void setFlags(VkImageCreateFlags flags);

        /**
         * @brief Set the image type for the Image.
         *
         * @param type The type of image being created. The image type is essentially the dimensionality of the image and can be VK_IMAGE_TYPE_1D,
         * VK_IMAGE_TYPE_2D or VK_IMAGE_TYPE_3D for a 1D, 2D or 3D image respectively.
         */
        void setImageType(VkImageType type);

        /**
         * @brief Set the format for the Image.
         *
         * @param format Describes how texel data is stored in memory and interpreted by Vulkan.
         */
        void setFormat(VkFormat format);

        /**
         * @brief Set the extent for the Image.
         *
         * @param extent The size of the image in texels. This should be an instance of the VkExtent3D structure , which has three members: width,
         * height, and depth. These should be set respectively to the width, height and depth of the desired image. For 1D images, the height should
         * be set to 1, and for 1D and 2D images, the depth should be set to 1.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkExtent3D.html
         */
        void setExtent(VkExtent3D extent);

        /**
         * @brief Set the number of mipmap levels for the Image.
         *
         * @param mipLevels The number of mipmap levels to create in the image.
         */
        void setMipLevels(unsigned int mipLevels);

        /**
         * @brief Set the number of array layers for the Image.
         *
         * @param arrayLayers
         */
        void setArrayLayers(unsigned int arrayLayers);

        /**
         * @brief Set the sample count for the Image.
         *
         * @param samples The number of samples in the image. It must be a member of the VkSampleCountFlagBits-enumerant.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSampleCountFlagBits.html
         */
        void setSamples(VkSampleCountFlagBits samples);

        /**
         * @brief Set the image tiling for the Image.
         *
         * @param tiling A member of the VkImageTiling-enumerant, which contains only VK_IMAGE_TILING_LINEAR or VK_IMAGE_TILING_OPTIMAL. Linear tiling
         * means that image data is laid out from left to right, top to bottom, so that if the underlying memory is mapped and it is written with the
         * CPU, it would form a linear image. Meanwhile, optimal tiling is an opaque display used by Vulkan to store data in memory to improve the
         * efficiency of the memory subsystem on the device. This is generally what should be chosen unless the image needs to be CPU mapped and
         * manipulated. Optimal tiling is likely to outperform linear tiling in most operations, and linear tiling may not be supported at all for
         * some operations or formats, depending on the Vulkan implementation.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageTiling.html
         */
        void setImageTiling(VkImageTiling tiling);

        /**
         * @brief Set the usage for the Image.
         *
         * @param usage A bitmask describing the intended usage for the image consisting of members of the VkImageUsageFlagBits-enumerant.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageUsageFlagBits.html
         */
        void setImageUsage(VkImageUsageFlags usage);

        /**
         * @brief Set the sharing mode for the Image.
         *
         * @param sharingMode A member of the VkSharingMode-enumerant indicating how the image will be used in the multiple device queues supported
         * by the device. Because Vulkan can run many commands in parallel, some implementations need to know whether the image will essentially be
         * used by a single command at a time or possibly by several. Setting sharingMode to VK_SHARING_MODE_EXCLUSIVE tell Vulkan that the image
         * will only be used for a single queue, while setting sharingMode to VK_SHARING_MODE_CONCURRENT specifies that the application will use the
         * image on multiple queues at once. Using VK_SHARING_MODE_CONCURRENT may result in lower performance on some systems, so unless necessary,
         * sharingMode should be set to VK_SHARING_MODE_EXCLUSIVE.
         */
        void setSharingMode(VkSharingMode sharingMode);

        /**
         * @brief Set the queue family indices for the Image.
         *
         * @param queueFamilyIndices An array of queue family indices on which the Image will be used.
         */
        void setQueueFamilyIndices(std::vector<uint32_t>& queueFamilyIndices);

        /**
         * @brief Set the queue family indices for the Image.
         *
         * @param initialLayout Images have a layout, which partially indicates how they will be used at a given time. This field determines the
         * layout in which the image is created. The available layouts are the members of the VkImageLayout-enumerant.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageLayout.html
         * Images should initially be created in the format VK_IMAGE_LAYOUT_UNDEFINED or VK_IMAGE_LAYOUT_PREINITIALIZED.
         * VK_IMAGE_LAYOUT_PREINITIALIZED should only be used if there is data in memory that is bound immediately to the image source.
         * VK_IMAGE_LAYOUT_UNDEFINED should be used when moving the resource to another layout before use. Images can be moved out of the
         * VK_IMAGE_LAYOUT_UNDEFINED layout at any time with little or no time cost.
         */
        void setInitialLayout(VkImageLayout initialLayout);

        void reset();

        std::unique_ptr<Image> getResult();
    };
} // namespace fillcan