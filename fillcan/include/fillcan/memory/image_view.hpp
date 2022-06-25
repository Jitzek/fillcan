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
        ImageView(LogicalDevice* pLogicalDevice, Image* pImage, VkImageViewType viewType, VkFormat format, VkImageSubresourceRange subresourceRange,
                  VkComponentMapping components);
        ~ImageView();

        ImageView(const ImageView&) = delete;
        ImageView& operator=(const ImageView&) = delete;

        VkImageView getImageViewHandle();
    };
} // namespace fillcan