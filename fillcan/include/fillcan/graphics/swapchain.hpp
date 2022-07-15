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

    /**
     * @brief The Swapchain Image structure is used by the Swapchain to keep track of the information needed for rendering to and presenting of
     * Swapchain Images.
     */
    struct SwapchainImage {
        /**
         * @brief Whether the Swapchain has become incompatible with the surface and can no longer be used for rendering. Usually happens after a
         * Window resize.
         */
        bool outOfDate;

        /**
         * @brief The index of the Swapchain Image.
         */
        unsigned int index;

        /**
         * @brief A pointer to the Image View of the Swapchain Image.
         */
        ImageView* pSwapchainImageView;

        /**
         * @brief A pointer to the Depth Image View of the Swapchain Image.
         */
        ImageView* pDepthImageView;

        /**
         * @brief A pointer to a Semaphore which will be signaled if the Image can be rendered to.
         */
        Semaphore* pSemaphoreImageReady = nullptr;

        /**
         * @brief A pointer to a Semaphore which will be signaled if the Image can be presented.
         */
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
         * Setting imageCount to 2 enables double buffering. Setting imageCount to 3 enables triple buffering. Setting imageCount to 1 represents a
         * request to render directly to the frontbuffer or to the screen.
         * Setting imageCount to 2 means that one frontbuffer and one backbuffer will
         * be created. After the presentation of a completed backbuffer is activated, rendering to the frontbuffer cannot begin until the
         * presentation of the frontbuffer has completed.
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

        /**
         * @brief Get the handle to the Vulkan Swapchain.
         *
         * @return The handle to the Vulkan Swapchain.
         */
        const VkSwapchainKHR getSwapchainHandle() const;

        /**
         * @brief Get the next available Swapchain Image.
         *
         * @details The images of the Swapchain are not immediately usable. Before data can be written into it, the next available image must be
         * obtained.
         *
         * @param pFence A pointer to a Fence which will be signaled once it's safe to render to the acquired Image.
         *
         * @return A SwapchainImage-struct containing the necessary information for rendering to the Swapchain Image.
         */
        SwapchainImage getNextImage(Fence* pFence = nullptr);

        /**
         * @brief Get the supported Swapchain format and colorspace pair.
         *
         * @return A VkSurfaceFormatKHR describing the supported Swapchain format and colorspace pair.
         * @see https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkSurfaceFormatKHR.html
         */
        VkSurfaceFormatKHR getSurfaceFormat();

        /**
         * @brief Get the amount of Swapchain Images supported by this Swapchain.
         *
         * @return The amount of Swapchain Images supported by this Swapchain.
         */
        uint32_t getImageCount();

        /**
         * @brief Get the amount of array layers a Swapchain Image of this Swapchain supports.
         *
         * @return The amount of array layers a Swapchain Image of this Swapchain supports.
         */
        unsigned int getImageArrayLayers();

        /**
         * @brief Get the intended usage for a Swapchain Image of this Swapchain.
         *
         * @return A bitmap of VkImageUsageFlagBits describing the intended usage for a Swapchain Image of this Swapchain.
         * @see https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkImageUsageFlagBits.html
         */
        VkImageUsageFlags getImageUsage();

        /**
         * @brief Get the Image sharing mode describing how the Swapchain Image of this Swapchain can be accessed from Queues.
         *
         * @return A member of the VkSharingMode-enumerant describing the Image sharing mode for the Swapchain Images of this Swapchain.
         * @see https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkSharingMode.html
         */
        VkSharingMode getImageSharingMode();

        /**
         * @brief Get the extent (the width and height) of the Swapchain Images of this Swapchain.
         *
         * @return A VkExtend2D-structure describing the width and height of the Swapchain Images of this Swapchain.
         * @see https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkExtent2D.html
         */
        VkExtent2D getImageExtent();

        /**
         * @brief Get the current presentation mode for the surface of this Swapchain.
         *
         * @return A member of the VkPresentModeKHR-enumerant describing the current presentation mode of this Swapchain.
         * @see https://www.khronos.org/registry/vulkan/specs/1.3-extensions/man/html/VkPresentModeKHR.html
         */
        VkPresentModeKHR getPresentMode();

        /**
         * @brief Get the queue families between which an image is shared.
         *
         * @return A list of queue family indices between which an image is shared.
         */
        const std::vector<uint32_t>& getQueueFamilyIndices() const;

        /**
         * @brief Present a Swapchain Image to the Window surface.
         *
         * @param pSwapchainImage A pointer to the SwapchainImage-structure containing the Image that should be presented.
         * @param waitSemaphores The Semaphores to wait for before presenting the Image.
         * @return true if the presentation was succesful.
         * @return false if the presentation failed.
         */
        bool present(SwapchainImage* pSwapchainImage, std::vector<VkSemaphore> waitSemaphores);
    };
} // namespace fillcan