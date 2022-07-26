#pragma once

// fillcan
#include "vulkan/vulkan_core.h"
#include <fillcan/memory/image_builder.hpp>

namespace fillcan {
    class LogicalDevice;
    class Image;
    class ImageDirector {
      private:
        ImageBuilder builder;

      public:
        /**
         * @brief Create a new Image Director.
         *
         * @details The Image Director class is part of the creational design pattern to construct complex objects step by step.
         * The director defines the order in which to execute building steps, while the builder provides the implementation for those steps.
         * The Image Director defines methods for constructing frequently used Image configurations. For it's methods it takes in the Logical Device
         * with which the Image should be associated with, the widht and height of the Image, the sample count of the Image and the sharing mode of
         * the Image, which will default to VK_SHARING_MODE_EXCLUSIVE most of the time. With this information it will use the Image Builder to
         * construct the requested Image which it will then return as a unique pointer which ownership will be moved to the application.
         */
        ImageDirector();
        ~ImageDirector();

        /**
         * @brief Create a new 2D texture.
         *
         * @param pLogicalDevice The Logical Device the Image should be associated with.
         * @param width The width the Image should have.
         * @param height The height the Image should have.
         * @param samples The sample count the Image should have.
         * @param sharingMode A member of the VkSharingMode-enumerant indicating how the image will be used in the multiple device queues supported
         * by the device.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSharingMode.html
         *
         * @return A unique pointer to the Image, it's ownership will be moved.
         * @throws std::runtime_error if a supported format could not be found.
         */
        std::unique_ptr<Image> make2DTexture(LogicalDevice* pLogicalDevice, unsigned int width, unsigned int height, VkSampleCountFlagBits samples,
                                             VkSharingMode sharingMode = VK_SHARING_MODE_EXCLUSIVE);

        /**
         * @brief Create a new Depth Image.
         *
         * @param pLogicalDevice The Logical Device the Image should be associated with.
         * @param width The width the Image should have.
         * @param height The height the Image should have.
         * @param samples The sample count the Image should have.
         * @param sharingMode A member of the VkSharingMode-enumerant indicating how the image will be used in the multiple device queues supported
         * by the device.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSharingMode.html
         *
         * @return A unique pointer to the Image, it's ownership will be moved.
         * @throws std::runtime_error if a supported format could not be found.
         */
        std::unique_ptr<Image> makeDepthImage(LogicalDevice* pLogicalDevice, unsigned int width, unsigned int height, VkSampleCountFlagBits samples,
                                              VkSharingMode sharingMode = VK_SHARING_MODE_EXCLUSIVE);
    };
} // namespace fillcan