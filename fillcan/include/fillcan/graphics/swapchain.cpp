// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/commands/queue.hpp>
#include <fillcan/graphics/swapchain.hpp>
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/memory/image.hpp>
#include <fillcan/memory/image_director.hpp>
#include <fillcan/memory/image_view.hpp>
#include <fillcan/memory/memory.hpp>
#include <fillcan/window.hpp>

// std
#include <memory>
#include <stdexcept>
#include <vector>

namespace fillcan {
    Swapchain::Swapchain(LogicalDevice* pLogicalDevice, Window* pWindow, Queue* pPresentQueue, uint32_t imageCount, VkPresentModeKHR presentMode,
                         Swapchain* pOldSwapchain)
        : pLogicalDevice(pLogicalDevice), pWindow(pWindow), pQueue(pPresentQueue), presentMode(presentMode) {

        const std::vector<VkSurfaceFormatKHR> surfaceFormats = this->pLogicalDevice->getPhysicalDevice()->getSurfaceFormatsKHR();
        for (VkSurfaceFormatKHR surfaceFormat : surfaceFormats) {
            if (surfaceFormat.format == VK_FORMAT_R8G8B8A8_SRGB || surfaceFormat.format == VK_FORMAT_B8G8R8A8_SRGB) {
                this->surfaceFormat = surfaceFormat;
                break;
            }
            if (surfaceFormat.format != VK_FORMAT_UNDEFINED) {
                this->surfaceFormat = surfaceFormat;
            }
        }
        VkSurfaceCapabilitiesKHR surfaceCapabilities = this->pLogicalDevice->getPhysicalDevice()->getSurfaceCapabilitiesKHR();

        const std::vector<VkPresentModeKHR> surfacePresentModes = this->pLogicalDevice->getPhysicalDevice()->getSurfacePresentModesKHR();
        if (std::count(surfacePresentModes.begin(), surfacePresentModes.end(), presentMode) == 0) {
            // Requested present mode is not supported, using fallback present mode
            this->presentMode = VK_PRESENT_MODE_FIFO_KHR;
        }

        VkSwapchainCreateInfoKHR swapchainCreateInfo = {};
        swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        swapchainCreateInfo.pNext = nullptr;
        swapchainCreateInfo.flags = 0;
        swapchainCreateInfo.surface = this->pWindow->getSurface();
        swapchainCreateInfo.minImageCount = imageCount;
        swapchainCreateInfo.imageFormat = this->surfaceFormat.format;
        swapchainCreateInfo.imageColorSpace = this->surfaceFormat.colorSpace;
        swapchainCreateInfo.imageExtent = surfaceCapabilities.currentExtent;
        swapchainCreateInfo.imageArrayLayers = 1;
        swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        swapchainCreateInfo.queueFamilyIndexCount = 0;
        swapchainCreateInfo.pQueueFamilyIndices = nullptr;
        swapchainCreateInfo.preTransform = surfaceCapabilities.currentTransform;
        swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        swapchainCreateInfo.presentMode = this->presentMode;
        swapchainCreateInfo.clipped = VK_TRUE;
        swapchainCreateInfo.oldSwapchain = pOldSwapchain != nullptr ? pOldSwapchain->getSwapchainHandle() : VK_NULL_HANDLE;

        if (vkCreateSwapchainKHR(this->pLogicalDevice->getLogicalDeviceHandle(), &swapchainCreateInfo, nullptr, &this->hSwapchain) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create swapchain");
        }

        uint32_t swapchainImageCount = 0;
        if (vkGetSwapchainImagesKHR(this->pLogicalDevice->getLogicalDeviceHandle(), this->hSwapchain, &swapchainImageCount, nullptr) != VK_SUCCESS) {
            throw std::runtime_error("Failed to get swapchain images");
        }

        std::vector<VkImage> hSwapchainImages;
        hSwapchainImages.resize(swapchainImageCount);
        if (vkGetSwapchainImagesKHR(this->pLogicalDevice->getLogicalDeviceHandle(), this->hSwapchain, &swapchainImageCount,
                                    hSwapchainImages.data()) != VK_SUCCESS) {
            throw std::runtime_error("Failed to get swapchain images");
        }

        this->upSwapchainImages.resize(swapchainImageCount);
        this->upImageReadySemaphores.resize(swapchainImageCount);
        this->upPresentReadySemaphores.resize(swapchainImageCount);
        this->upDepthImages.resize(swapchainImageCount);
        this->upDepthImageMemories.resize(swapchainImageCount);

        ImageDirector imageDirector{};
        for (size_t i = 0; i < this->getImageCount(); i++) {
            // Prepare swapchain images which need to contain the necessary image views
            this->upSwapchainImages.at(i) = std::move(std::make_unique<Image>(this->pLogicalDevice, this, hSwapchainImages.at(i)));
            this->upSwapchainImages.at(i)->createImageView(
                VK_IMAGE_VIEW_TYPE_2D, this->surfaceFormat.format,
                {.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT, .baseMipLevel = 0, .levelCount = 1, .baseArrayLayer = 0, .layerCount = 1});

            // Create semaphores for when image is ready to be rendered to and when the image is ready to be presented
            this->upImageReadySemaphores.at(i) = std::move(std::make_unique<Semaphore>(this->pLogicalDevice));
            this->upPresentReadySemaphores.at(i) = std::move(std::make_unique<Semaphore>(this->pLogicalDevice));

            // Prepare depth images which need to contain the necessary image views for depth buffering
            this->upDepthImages.at(i) = std::move(imageDirector.makeDepthImage(this->pLogicalDevice, this->getImageExtent().width,
                                                                               this->getImageExtent().height, VK_SAMPLE_COUNT_1_BIT));
            this->upDepthImageMemories.at(i) =
                std::move(std::make_unique<Memory>(this->pLogicalDevice, this->upDepthImages.at(i).get(), VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT));
            this->upDepthImages.at(i)->bindMemory(this->upDepthImageMemories.at(i).get());
            this->upDepthImages.at(i)->createImageView(
                VK_IMAGE_VIEW_TYPE_2D, this->upDepthImages.at(i)->getFormat(),
                {.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT, .baseMipLevel = 0, .levelCount = 1, .baseArrayLayer = 0, .layerCount = 1});
        }
    }

    Swapchain::~Swapchain() {
        if (this->pLogicalDevice == nullptr) {
            std::cerr << "Failed to destroy Swapchain: Logical Device was NULL"
                      << "\n";
        }
        if (this->hSwapchain == VK_NULL_HANDLE) {
            std::cerr << "Failed to destroy Swapchain: Handle was VK_NULL_HANDLE"
                      << "\n";
        }
        vkDestroySwapchainKHR(this->pLogicalDevice->getLogicalDeviceHandle(), this->hSwapchain, nullptr);
    }

    const VkSwapchainKHR Swapchain::getSwapchainHandle() const { return this->hSwapchain; }

    uint32_t Swapchain::getImageCount() { return this->upSwapchainImages.size(); }

    unsigned int Swapchain::getImageArrayLayers() { return this->imageArrayLayers; }

    VkImageUsageFlags Swapchain::getImageUsage() { return this->imageUsage; }

    VkSharingMode Swapchain::getImageSharingMode() { return this->imageSharingMode; }

    VkPresentModeKHR Swapchain::getPresentMode() { return this->presentMode; }

    const std::vector<uint32_t>& Swapchain::getQueueFamilyIndices() const { return this->queueFamilyIndices; }

    SwapchainImage Swapchain::getNextImage(Fence* pFence) {
        uint32_t swapchainImageIndex = 0;
        VkResult acquireNextImageResult = vkAcquireNextImageKHR(this->pLogicalDevice->getLogicalDeviceHandle(), this->hSwapchain, UINT64_MAX,
                                                                this->upImageReadySemaphores.at(this->currentImageIndex)->getSemaphoreHandle(),
                                                                pFence != nullptr ? pFence->getFenceHandle() : VK_NULL_HANDLE, &swapchainImageIndex);
        if (acquireNextImageResult == VK_ERROR_OUT_OF_DATE_KHR) {
            return {.outOfDate = true, .index = 0, .pSwapchainImageView = nullptr, .pSemaphoreImageReady = nullptr};
        }
        if (acquireNextImageResult != VK_SUCCESS && acquireNextImageResult != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("Failed to acquire next swapchain image");
        }

        SwapchainImage returnImage = {.outOfDate = false,
                                      .index = swapchainImageIndex,
                                      .pSwapchainImageView = this->upSwapchainImages.at(this->currentImageIndex)->getImageView(0),
                                      .pDepthImageView = this->upDepthImages.at(this->currentImageIndex)->getImageView(0),
                                      .pSemaphoreImageReady = this->upImageReadySemaphores[this->currentImageIndex].get(),
                                      .pSemaphorePresentReady = this->upPresentReadySemaphores.at(this->currentImageIndex).get()};
        this->currentImageIndex = (this->currentImageIndex + 1) % (this->getImageCount());
        return returnImage;
    }

    VkSurfaceFormatKHR Swapchain::getSurfaceFormat() { return this->surfaceFormat; }

    bool Swapchain::present(SwapchainImage* pSwapchainImage, std::vector<VkSemaphore> waitSemaphores) {
        if (pSwapchainImage == nullptr) {
            return false;
        }
        VkPresentInfoKHR presentInfo = {};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        presentInfo.pNext = nullptr;
        if (waitSemaphores.size() > 0) {
            presentInfo.waitSemaphoreCount = static_cast<uint32_t>(waitSemaphores.size());
            presentInfo.pWaitSemaphores = waitSemaphores.data();
        } else {
            presentInfo.waitSemaphoreCount = 0;
            presentInfo.pWaitSemaphores = nullptr;
        }
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = &this->hSwapchain;
        presentInfo.pImageIndices = &pSwapchainImage->index;

        if (vkQueuePresentKHR(this->pQueue->getQueueHandle(), &presentInfo) != VK_SUCCESS) {
            return false;
        }
        return true;
    }

    VkExtent2D Swapchain::getImageExtent() { return this->pWindow->getExtent(); }
} // namespace fillcan