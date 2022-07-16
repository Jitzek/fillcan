#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

namespace fillcan {
    class LogicalDevice;
    class Image;
    class ImageView {
      private:
        VkImageView hImageView;
        LogicalDevice* pLogicalDevice;
        VkImageViewType viewType;
        VkFormat format;
        VkComponentMapping components;
        VkImageSubresourceRange subresourceRange;

      public:
        /**
         * @brief Create a new Image View.
         *
         * @details In many cases, the image resource cannot be used directly because it requires more information than is contained in the resource
         * itself. For example, an image resource cannot be used directly as an attachment to a framebuffer or bound in a descriptor set to be sampled
         * in a shader. To meet these additional requirements, an image view must be created, which is essentially a collection of properties and a
         * reference to a parent image resource.
         *
         * An image view also makes it possible to view all or part of an existing image as a different format. The resulting view of the parent image
         * must have the same dimensions as the parent image, although a subset of the array layers or mip levels of the parent image may be included
         * in the view. The format of the parent and child images must also be compatible, which usually means they have the same number of bits per
         * pixel, even if the data formats are completely different and even if there is a different number of channels in the image.
         *
         * @param pLogicalDevice A pointer to the Logical Device the Image View should be associated with.
         * @param pImage A pointer to the parent Image to create a Image View of.
         * @param viewType The type of view to create. The display type must be compatible with the parent image type and is a member of the
         * VkImageViewType-enumeration, which is larger than the VkImageType-enumeration used when creating the parent image.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageViewType.html
         * @param format The format of the new view. This must be a format compatible with the parent image. If two formats have the same number of
         * bits per pixel, they are generally considered compatible.
         * @param subresourceRange The Image View can be a subset of the parent image. This subset is specified using the embedded
         * VkImageSubresourceRange-structure.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageSubresourceRange.html
         * @param components The order of the components in the view may differ from that in the parent image. This makes it possible, for example, to
         * create an RGBA representation of an image in BGRA format. This remapping is specified using an instance of the
         * VkComponentMapping-structure.
         */
        ImageView(LogicalDevice* pLogicalDevice, Image* pImage, VkImageViewType viewType, VkFormat format, VkImageSubresourceRange subresourceRange,
                  VkComponentMapping components);
        ~ImageView();
        ImageView(const ImageView&) = delete;
        ImageView& operator=(const ImageView&) = delete;

        const VkImageView getImageViewHandle() const;
    };
} // namespace fillcan