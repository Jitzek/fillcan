#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <cstdint>
#include <fillcan/memory/fence.hpp>
#include <fillcan/memory/image.hpp>
#include <fillcan/memory/semaphore.hpp>

// std
#include <memory>
#include <utility>
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class Window;
    class Queue;
    class CommandBuffer;

    struct SwapchainImage {
        bool outOfDate;
        unsigned int index;
        Image* pImage;
        Semaphore* pSemaphore = nullptr;
    };

    class Swapchain {
      private:
        VkSwapchainKHR hSwapchain;
        LogicalDevice* pLogicalDevice;
        Window* pWindow;
        Queue* pQueue;
        VkSurfaceFormatKHR surfaceFormat{.format = VK_FORMAT_UNDEFINED, .colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
        uint32_t imageCount = 3;
        unsigned int imageArrayLayers = 1;
        VkImageUsageFlags imageUsage = 0;
        VkSharingMode imageSharingMode = VK_SHARING_MODE_MAX_ENUM;
        std::vector<uint32_t> queueFamilyIndices = {};
        std::vector<std::unique_ptr<Image>> upSwapchainImages = {};
        std::vector<std::unique_ptr<Semaphore>> upSemaphores = {};
        std::vector<VkImage> hSwapchainImages = {};

      public:
        Swapchain(LogicalDevice* pLogicalDevice, Window* pWindow, Queue* pPresentQueue, uint32_t imageCount = 3,
                  VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR, Swapchain* pOldSwapchain = VK_NULL_HANDLE);
        ~Swapchain();

        VkSwapchainKHR getSwapchainHandle();
        SwapchainImage getNextImage(Fence* pFence = nullptr);
        VkSurfaceFormatKHR getSurfaceFormat();

        uint32_t getImageCount();
        unsigned int getImageArrayLayers();
        VkImageUsageFlags getImageUsage();
        VkSharingMode getImageSharingMode();
        std::vector<uint32_t>& getQueueFamilyIndices();

        bool present(SwapchainImage* pSwapchainImage, std::vector<VkSemaphore> waitSemaphores);

        VkExtent2D getImageExtent();
    };
} // namespace fillcan