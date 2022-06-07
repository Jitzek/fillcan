#pragma once

// fillcan
#include <fillcan/memory/image_builder.hpp>

namespace fillcan {
    class LogicalDevice;
    class Image;
    class ImageDirector {
      private:
        ImageBuilder builder;
      public:
        ImageDirector();
        ~ImageDirector();

        std::unique_ptr<Image> make2DTexture(LogicalDevice* pLogicalDevice, unsigned int width, unsigned int height, VkSampleCountFlagBits samples);
    };
} // namespace fillcan