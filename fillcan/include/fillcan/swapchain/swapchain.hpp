#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

namespace fillcan {
    class LogicalDevice;
    class Window;

    struct SwapchainImage {
        unsigned int index;
        VkImage hImage;
    };

    enum BufferMode { FILLCAN_SINGLE_BUFFERING = 1, FILLCAN_DOUBLE_BUFFERING = 2, FILLCAN_TRIPLE_BUFFERING = 3 };

    class Swapchain {
      private:
        VkSwapchainKHR hSwapchain;
        LogicalDevice* pLogicalDevice;
        Window* pWindow;
        VkSurfaceFormatKHR surfaceFormat{.format = VK_FORMAT_UNDEFINED, .colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};

      public:
        Swapchain(LogicalDevice* pLogicalDevice, Window* pWindow, BufferMode bufferMode = FILLCAN_TRIPLE_BUFFERING,
                  VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR, Swapchain* pOldSwapchain = VK_NULL_HANDLE);
        ~Swapchain();

        VkSwapchainKHR getSwapchainHandle();
        SwapchainImage& getNextImage();
        VkSurfaceFormatKHR getSurfaceFormat();

        void present(SwapchainImage& swapchainImage, VkSemaphore* pSemaphore = nullptr);
    };
} // namespace fillcan