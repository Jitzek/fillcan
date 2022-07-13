#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/memory/fence.hpp>
#include <fillcan/memory/image.hpp>
#include <fillcan/memory/memory.hpp>
#include <fillcan/memory/semaphore.hpp>

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
        ImageView* pSwapchainImageView;
        ImageView* pDepthBufferImageView;
        Semaphore* pSemaphoreImageReady = nullptr;
        Semaphore* pSemaphorePresentReady = nullptr;
    };

    class Swapchain {
      private:
        VkSwapchainKHR hSwapchain;
        LogicalDevice* pLogicalDevice;
        Window* pWindow;
        Queue* pQueue;
        VkSurfaceFormatKHR surfaceFormat = {VK_FORMAT_MAX_ENUM, VK_COLOR_SPACE_MAX_ENUM_KHR};
        uint32_t imageCount = 3;
        unsigned int imageArrayLayers = 1;
        VkImageUsageFlags imageUsage = 0;
        VkSharingMode imageSharingMode = VK_SHARING_MODE_MAX_ENUM;
        VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR;
        std::vector<uint32_t> queueFamilyIndices = {};
        std::vector<std::unique_ptr<Semaphore>> upImageReadySemaphores = {};
        std::vector<std::unique_ptr<Semaphore>> upPresentReadySemaphores = {};
        std::vector<std::unique_ptr<Image>> upSwapchainImages = {};
        std::vector<std::unique_ptr<Image>> upDepthImages = {};
        std::vector<std::unique_ptr<Memory>> upDepthImageMemories = {};

        uint32_t currentImageIndex = 0;

      public:
        /**
         * @brief Create a new Swapchain.
         *
         * @details Swapchain objects are used to ask the window system to create one or more images that can be used to present on a Vulkan surface
         * (this is visible with the VK_KHR_surface extension). Each Swapchain object manages a series of Images, usually in some form of a ring
         * buffer. The application can ask the Swapchain for the next available Image, render to it, and then return the Image to the swapchain ready
         * for display. By managing presentable images in a ring or queue, one Image can be displayed on the screen while another is drawn to by the
         * application, overlapping the operation of the window system and the application.
         *
         * @param pLogicalDevice A pointer to the Logical Device to associate the Swapchain with.
         * @param pWindow A pointer to the Window of which surface the Swapchain should make presentable Images for.
         * @param pPresentQueue The Queue which the Swapchain should use for presentation.
         * @param imageCount The amount of Images the Swapchain should prepare.
         * @param presentMode The presentation mode for the surface. This should be a member of the VkPresentModeKHR-enumerant.
         * @see https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkPresentModeKHR.html
         * @param pOldSwapchain A pointer to the old Swapchain which can be used to return an existing Swapchain associated with the surface to Vulkan
         * for recycling. This will be used when one Swapchain is replaced by another, such as when a Window is resized and the Swapchain needs to be
         * remapped with larger images.
         */
        Swapchain(LogicalDevice* pLogicalDevice, Window* pWindow, Queue* pPresentQueue, uint32_t imageCount = 3,
                  VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR, Swapchain* pOldSwapchain = nullptr);
        ~Swapchain();
        Swapchain(const Swapchain&) = delete;
        Swapchain& operator=(const Swapchain&) = delete;

        VkSwapchainKHR getSwapchainHandle();

        SwapchainImage getNextImage(Fence* pFence = nullptr);

        VkSurfaceFormatKHR getSurfaceFormat();

        uint32_t getImageCount();

        unsigned int getImageArrayLayers();

        VkImageUsageFlags getImageUsage();

        VkSharingMode getImageSharingMode();

        VkExtent2D getImageExtent();

        VkPresentModeKHR getPresentMode();

        std::vector<uint32_t>& getQueueFamilyIndices();

        bool present(SwapchainImage* pSwapchainImage, std::vector<VkSemaphore> waitSemaphores);
    };
} // namespace fillcan