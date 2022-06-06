
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
        ImageView(LogicalDevice* pLogicalDevice, Image* pImage, VkImageViewType viewType, VkFormat format,
                  VkImageSubresourceRange subresourceRange = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1}, VkComponentMapping components = {});
        ~ImageView();

        VkImageView getImageViewHandle();
    };
} // namespace fillcan