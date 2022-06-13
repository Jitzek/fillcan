#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/memory/image.hpp>

// std
#include <memory>
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class Window;
    class Queue;
    class CommandBuffer;

    struct SwapchainImage {
        bool outOfDate;
        unsigned int index;
        std::unique_ptr<Image> upImage;
        VkSemaphore hSemaphore = VK_NULL_HANDLE;
    };

    enum BufferMode { FILLCAN_BUFFERING_UNDEFINED = -1, FILLCAN_BUFFERING_SINGLE = 1, FILLCAN_BUFFERING_DOUBLE = 2, FILLCAN_BUFFERING_TRIPLE = 3 };

    class Swapchain {
      private:
        VkSwapchainKHR hSwapchain;
        LogicalDevice* pLogicalDevice;
        Window* pWindow;
        Queue* pQueue;
        VkSurfaceFormatKHR surfaceFormat{.format = VK_FORMAT_UNDEFINED, .colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
        BufferMode bufferMode = FILLCAN_BUFFERING_UNDEFINED;
        unsigned int imageArrayLayers = 1;
        VkImageUsageFlags imageUsage = 0;
        VkSharingMode imageSharingMode = VK_SHARING_MODE_MAX_ENUM;
        std::vector<uint32_t> queueFamilyIndices = {};
        std::vector<Image> swapchainImages = {};
        std::vector<VkImage> hSwapchainImages = {};

      public:
        Swapchain(LogicalDevice* pLogicalDevice, Window* pWindow, Queue* pPresentQueue, BufferMode bufferMode = FILLCAN_BUFFERING_TRIPLE,
                  VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR, Swapchain* pOldSwapchain = VK_NULL_HANDLE);
        ~Swapchain();

        VkSwapchainKHR getSwapchainHandle();
        SwapchainImage getNextImage(CommandBuffer* pCommandBuffer = nullptr);
        VkSurfaceFormatKHR getSurfaceFormat();

        BufferMode getBufferMode();
        unsigned int getImageArrayLayers();
        VkImageUsageFlags getImageUsage();
        VkSharingMode getImageSharingMode();
        std::vector<uint32_t>& getQueueFamilyIndices();

        void present(SwapchainImage* pSwapchainImage, std::vector<VkSemaphore> semaphores);

        VkExtent2D getImageExtent();
    };
} // namespace fillcan