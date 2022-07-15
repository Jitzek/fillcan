#pragma once

// vulkan
#include "fillcan/commands/command_buffer.hpp"
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
         * @param flags A bitmask of VkImageCreateFlagBits that describe some properties of the image.
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
         * @param samples The number of samples in the image. It must be a member of the VkSampleCountFlagBits-enumerant.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSampleCountFlagBits.html
         * @param tiling A member of the VkImageTiling-enumerant, which contains only VK_IMAGE_TILING_LINEAR or VK_IMAGE_TILING_OPTIMAL. Linear tiling
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
         * @param queueFamilyIndices An array of queue family indices on which the Image will be used.
         * @param initialLayout Images have a layout, which partially indicates how they will be used at a given time. This field determines the
         * layout in which the image is created. The available layouts are the members of the VkImageLayout-enumerant.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageLayout.html
         * Images should initially be created in the format VK_IMAGE_LAYOUT_UNDEFINED or VK_IMAGE_LAYOUT_PREINITIALIZED.
         * VK_IMAGE_LAYOUT_PREINITIALIZED should only be used if there is data in memory that is bound immediately to the image source.
         * VK_IMAGE_LAYOUT_UNDEFINED should be used when moving the resource to another layout before use. Images can be moved out of the
         * VK_IMAGE_LAYOUT_UNDEFINED layout at any time with little or no time cost.
         */
        Image(LogicalDevice* pLogicalDevice, VkImageCreateFlags flags, VkImageType type, VkFormat format, VkExtent3D extent, unsigned int mipLevels,
              unsigned int arrayLayers, VkSampleCountFlagBits samples, VkImageTiling tiling, VkImageUsageFlags usage, VkSharingMode sharingMode,
              std::vector<uint32_t>& queueFamilyIndices, VkImageLayout initialLayout);

        /**
         * @brief Wrap around a Swapchain Image.
         *
         * @param pLogicalDevice A pointer to the Logical Device the Swapchain Image is associated with.
         * @param pSwapchain A pointer to the Swapchain which owns the Vulkan Image.
         * @param hImage The handle to the Vulkan Image to wrap around.
         *
         * @note This Constructor is primarily used by the Swapchain to create Image Views for it's images. By using this Constructor most getter
         * methods will return their default value.
         */
        Image(LogicalDevice* pLogicalDevice, Swapchain* pSwapchain, VkImage hImage);
        ~Image();
        Image(const Image&) = delete;
        Image& operator=(const Image&) = delete;

        /**
         * @brief Get the handle to the Vulkan Image.
         *
         * @return The handle to the Vulkan Image.
         */
        VkImage getImageHandle();

        /**
         * @brief Get the flags used for creating the Image.
         *
         * @return The flags set when creating of the Image.
         */
        VkImageCreateFlags getFlags();

        /**
         * @brief Get the intended usage of the Image.
         *
         * @return The intended usage of the Image.
         */
        VkImageUsageFlags getUsage();

        /**
         * @brief Get the sharing mode of the Image.
         *
         * @return The sharing mode of the Image.
         */
        VkSharingMode getSharingMode();

        /**
         * @brief Get the queue family indices of the Image.
         *
         * @return The queue family indices of the Image.
         */
        const std::vector<uint32_t>& getQueueFamilyIndices() const;

        /**
         * @brief Get the type of the Image.
         *
         * @return The type of the Image.
         */
        VkImageType getType();

        /**
         * @brief Get the format of the Image.
         *
         * @return The format of the Image.
         */
        VkFormat getFormat();

        /**
         * @brief Get the extent of the Image.
         *
         * @return The extent of the Image.
         */
        VkExtent3D getExtent();

        /**
         * @brief Get the amount of mipmap levels of the Image.
         *
         * @return The amount of mipmap levels of the Image.
         */
        unsigned int getMipLevels();

        /**
         * @brief Get the amount of array layers of the Image.
         *
         * @return The amount of array layers of the Image.
         */
        unsigned int getArrayLayers();

        /**
         * @brief Get the sample count of the Image.
         *
         * @return The sample count of the Image.
         */
        VkSampleCountFlagBits getSamples();

        /**
         * @brief Get the tiling of the Image.
         *
         * @return The tiling of the Image.
         */
        VkImageTiling getTiling();

        /**
         * @brief Get the initial layout of the Image.
         *
         * @return The initial layout of the Image.
         */
        VkImageLayout getInitialLayout();

        /**
         * @brief Bind Memory to the Image.
         *
         * @param pMemory A pointer to the Memory to bind to the Image.
         * @param memoryOffset Specifies the offset in the memory object the Image will live. If only one resource will be bound to the memory
         * object, this can be set to 0.
         */
        void bindMemory(Memory* pMemory, VkDeviceSize memoryOffset = 0);

        /**
         * @brief Get the Memory bound with Image#bindMemory.
         *
         * @return A pointer to the bound Memory, or nullptr if no Memory is bound.
         */
        const Memory* getMemory() const;

        /**
         * @brief Create an Image View.
         *
         * @param viewType The type of view to create. The display type must be compatible with the parent image type and is a member of the
         * VkImageViewType-enumeration, which is larger than the VkImageType enumeration used when creating the parent image.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageViewType.html
         * @param format The format of the new view. This must be a format compatible with the parent image. If two formats have the same number of
         * bits per pixel, they are generally considered compatible.
         * @param subresourceRange The Image View can be a subset of the parent image. This subset is specified using the embedded
         * VkImageSubresourceRange-structure.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageSubresourceRange.html
         * @param components The order of the components in the view may differ from that in the parent image. This makes it possible, for example, to
         * create an RGBA representation of an image in BGRA format. This remapping is specified using an instance of the
         * VkComponentMapping-structure.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkComponentMapping.html
         *
         * @return The index of the newly created Buffer View.
         */
        unsigned int createImageView(VkImageViewType viewType, VkFormat format,
                                     VkImageSubresourceRange subresourceRange = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1},
                                     VkComponentMapping components = {VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY,
                                                                      VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY});

        /**
         * @brief Get all the created Image Views.
         *
         * @return A list of pointers to the created Image Views.
         */
        std::vector<ImageView*> getImageViews();

        /**
         * @brief Get a pointer to a Image View by index.
         *
         * @param index The index the Image View to get.
         * @return A pointer to the requested Image View.
         */
        ImageView* getImageView(unsigned int index);

        /**
         * @brief Destroy all created Image Views.
         */
        void destroyImageViews();

        /**
         * @brief Destroy an Image View by index.
         *
         * @param index The index of the Image View to destroy.
         */
        void destroyImageView(unsigned int index);

        /**
         * @brief Copy this Image's data to a given Image.
         *
         * @param pCommandBuffer The Command Buffer to use to execute the copy.
         * @param pImage A pointer to the Image to copy this Image's data to.
         * @param srcLayout The layout of the source Image (this image) subresources for the copy. This should be a member of the
         * VkImageLayout-enumerant. This is most likely either VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_GENERAL or
         * VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR.
         * @param dstLayout The layout of the destination Image subresources for the copy. This should be a member of the VkImageLayout-enumerant.
         * This is most likely either VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_GENERAL or VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageLayout.html
         * @param regions An array of VkImageCopy-structures, each of which describes a region of data to copy.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageCopy.html
         */
        void copyTo(CommandBuffer* pCommandBuffer, Image* pImage, VkImageLayout srcLayout, VkImageLayout dstLayout,
                    std::vector<VkImageCopy>& regions);

        /**
         * @brief Copy this Image's data to a given Buffer.
         *
         * @param pCommandBuffer The Command Buffer to use to execute the copy.
         * @param pBuffer A pointer to the Buffer to copy this Image's data to.
         * @param srcLayout The layout of the source Image (this image) subresources for the copy. This should be a member of the
         * VkImageLayout-enumerant. This is most likely either VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_GENERAL or
         * VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageLayout.html
         * @param regions An array of VkBufferImageCopy-structures, each of which describes a region of data to copy.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkBufferImageCopy.html
         */
        void copyTo(CommandBuffer* pCommandBuffer, Buffer* pBuffer, VkImageLayout srcLayout, std::vector<VkBufferImageCopy>& regions);

        /**
         * @brief Transition an Image from one layout to another using an Vulkan Image Memory Barrier.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageMemoryBarrier.html
         *
         * @details Images are transferred from layout to layout using image memory barriers.
         * Image memory barriers are used to control access to an image. They make our operations on the GPU happen in a certain order, which ensures
         * that we get the expected result. A barrier separates two operations in a Queue: before the barrier and after the barrier. Work done before
         * the barrier is completed is always done before it can be used again.
         *
         * @param pCommandBuffer The Command Buffer to use to transfer the Image layout.
         * @param oldLayout The layout to be used before the barrier for the image. This is a member of the VkImageLayout-enumeration.
         * @param newLayout The layout to use after the barrier for the image. This is a member of the VkImageLayout-enumeration.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageLayout.html
         * @param srcAccessMask The access type of the source. This is a member of the VkAccessFlagBits-enumeration.
         * @param dstAccessMask The access type of the destination. This is a member of the VkAccessFlagBits-enumeration.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkAccessFlagBits.html
         * @param srcStageMask Which pipeline stages wrote to the source last. This is what happens before the barrier. Built from a number of members
         * of the VkPipelineStageFlagBits-enumeration.
         * The srcStageMask indicates when the source stage has finished reading or writing a source. As a result, moving that stage's effective
         * position later in the pipeline doesn't change the fact that those accesses have been completed; it can only mean that the implementation is
         * waiting longer than is really necessary to complete. So it also waits for all phases of the pipeline before the specified phase.
         * @param dstStageMask Which pipeline stages will read from the source. This is what happens after the barrier. Built from a number of members
         * of the VkPipelineStageFlagBits-enumeration.
         * The dstStageMask specifies the point at which the pipeline will wait before continuing. If an implementation moves that holdpoint before,
         * it will still work. The event it's waiting for will still complete when the later parts of the pipeline run. That implementation simply
         * misses the opportunity to perform work while it waited. Later phases in the pipeline after the specified phase are therefore also blocked.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineStageFlagBits.html
         * @param dependencyFlags Specifies a set of VkDependencyFlagBits-flags describing how the dependency represented by the barrier affects the
         * resources referenced by the barrier.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkDependencyFlagBits.html
         *
         * @note It is usually better to use render passes whenever possible for transferring images from layout to layout.
         */
        void transitionImageLayout(CommandBuffer* pCommandBuffer, VkImageLayout oldLayout, VkImageLayout newLayout, VkAccessFlags srcAccessMask,
                                   VkAccessFlags dstAccessMask, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask,
                                   VkDependencyFlags dependencyFlags = 0);
    };
} // namespace fillcan