#pragma once

// vulkan
#include "fillcan/memory/image.hpp"
#include "vulkan/vulkan_core.h"
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class Window;
    class Queue;
    class CommandBuffer;

    struct SwapchainImage {
        bool outOfDate;
        unsigned int index;
        Image image;
        VkSemaphore hSemaphore;
    };

    enum BufferMode { FILLCAN_SINGLE_BUFFERING = 1, FILLCAN_DOUBLE_BUFFERING = 2, FILLCAN_TRIPLE_BUFFERING = 3 };

    class Swapchain {
      private:
        VkSwapchainKHR hSwapchain;
        LogicalDevice* pLogicalDevice;
        Window* pWindow;
        Queue* pQueue;
        VkSurfaceFormatKHR surfaceFormat{.format = VK_FORMAT_UNDEFINED, .colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
        std::vector<VkImage> hSwapchainImages = {};

      public:
        Swapchain(LogicalDevice* pLogicalDevice, Window* pWindow, Queue* pPresentQueue, BufferMode bufferMode = FILLCAN_TRIPLE_BUFFERING,
                  VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR, Swapchain* pOldSwapchain = VK_NULL_HANDLE);
        ~Swapchain();

        VkSwapchainKHR getSwapchainHandle();
        SwapchainImage getNextImage(CommandBuffer* pCommandBuffer = nullptr);
        VkSurfaceFormatKHR getSurfaceFormat();

        bool isSwapchainImageValid(SwapchainImage& swapchainImage);

        void present(SwapchainImage& swapchainImage, VkSemaphore* pSemaphore = nullptr);

        VkExtent2D getExtent();
    };
} // namespace fillcan