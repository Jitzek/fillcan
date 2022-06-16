// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include "fillcan/memory/image_director.hpp"
#include "fillcan/memory/image_view.hpp"
#include <algorithm>
#include <fillcan/commands/queue.hpp>
#include <fillcan/graphics/swapchain.hpp>
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/memory/image.hpp>
#include <fillcan/window.hpp>

// std
#include <cstdint>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

namespace fillcan {
    Swapchain::Swapchain(LogicalDevice* pLogicalDevice, Window* pWindow, Queue* pPresentQueue, uint32_t imageCount, VkPresentModeKHR presentMode,
                         Swapchain* pOldSwapchain)
        : pLogicalDevice(pLogicalDevice), pWindow(pWindow), pQueue(pPresentQueue) {

        const std::vector<VkSurfaceFormatKHR> surfaceFormats = this->pLogicalDevice->getPhysicalDevice()->getSurfaceFormatsKHR();
        for (VkSurfaceFormatKHR surfaceFormat : surfaceFormats) {
            if (surfaceFormat.format == VK_FORMAT_R8G8B8A8_SRGB) {
                this->surfaceFormat = surfaceFormat;
                break;
            }
            if (surfaceFormat.format != VK_FORMAT_UNDEFINED) {
                this->surfaceFormat = surfaceFormat;
            }
        }
        VkSurfaceCapabilitiesKHR surfaceCapabilities = this->pLogicalDevice->getPhysicalDevice()->getSurfaceCapabilitiesKHR();

        const std::vector<VkPresentModeKHR> surfacePresentModes = this->pLogicalDevice->getPhysicalDevice()->getSurfacePresentModesKHR();
        if (!std::count(surfacePresentModes.begin(), surfacePresentModes.end(), presentMode)) {
            // Requested present mode is not supported, using fallback present mode
            presentMode = VK_PRESENT_MODE_FIFO_KHR;
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
        swapchainCreateInfo.presentMode = presentMode;
        swapchainCreateInfo.clipped = VK_TRUE;
        swapchainCreateInfo.oldSwapchain = pOldSwapchain != nullptr ? pOldSwapchain->getSwapchainHandle() : VK_NULL_HANDLE;

        if (vkCreateSwapchainKHR(this->pLogicalDevice->getLogicalDeviceHandle(), &swapchainCreateInfo, nullptr, &this->hSwapchain) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create swapchain");
        }

        uint32_t swapchainImageCount = 0;
        if (vkGetSwapchainImagesKHR(this->pLogicalDevice->getLogicalDeviceHandle(), this->hSwapchain, &swapchainImageCount, nullptr) != VK_SUCCESS) {
            throw std::runtime_error("Failed to get swapchain images");
        }
        this->hSwapchainImages.resize(swapchainImageCount);
        if (vkGetSwapchainImagesKHR(this->pLogicalDevice->getLogicalDeviceHandle(), this->hSwapchain, &swapchainImageCount,
                                    this->hSwapchainImages.data()) != VK_SUCCESS) {
            throw std::runtime_error("Failed to get swapchain images");
        }
        // for (VkImage hSwapchainImage : hSwapchainImages) {
        //     this->upSwapchainImages.push_back(std::move(std::make_unique<Image>(this->pLogicalDevice, this, hSwapchainImage)));
        // }
        this->upSwapchainImages.resize(swapchainImageCount);
        this->upImageReadySemaphores.resize(swapchainImageCount);
        this->upPresentReadySemaphores.resize(swapchainImageCount);
        for (size_t i = 0; i < this->getImageCount(); i++) {
            this->upImageReadySemaphores.at(i) = std::move(std::make_unique<Semaphore>(this->pLogicalDevice));
            this->upPresentReadySemaphores.at(i) = std::move(std::make_unique<Semaphore>(this->pLogicalDevice));
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

    VkSwapchainKHR Swapchain::getSwapchainHandle() { return this->hSwapchain; }

    uint32_t Swapchain::getImageCount() { return this->hSwapchainImages.size(); }

    unsigned int Swapchain::getImageArrayLayers() { return this->imageArrayLayers; }

    VkImageUsageFlags Swapchain::getImageUsage() { return this->imageUsage; }

    VkSharingMode Swapchain::getImageSharingMode() { return this->imageSharingMode; }

    VkPresentModeKHR Swapchain::getPresentMode() { return this->presentMode; }

    std::vector<uint32_t>& Swapchain::getQueueFamilyIndices() { return this->queueFamilyIndices; }

    SwapchainImage Swapchain::getNextImage(Fence* pFence) {
        uint32_t swapchainImageIndex = 0;
        // this->upImageReadySemaphores[this->currentImageIndex] = std::move(std::make_unique<Semaphore>(this->pLogicalDevice));

        // VkImageMemoryBarrier imageMemoryBarrier = {};
        // imageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        // imageMemoryBarrier.pNext = nullptr;
        // imageMemoryBarrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        // imageMemoryBarrier.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
        // imageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        // imageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
        // imageMemoryBarrier.srcQueueFamilyIndex = 0;
        // imageMemoryBarrier.dstQueueFamilyIndex = 0;
        // imageMemoryBarrier.image = this->hSwapchainImages[imageIndex];
        // imageMemoryBarrier.subresourceRange = (VkImageSubresourceRange){.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
        //                                                                 .baseMipLevel = 0,
        //                                                                 .levelCount = VK_REMAINING_MIP_LEVELS,
        //                                                                 .baseArrayLayer = 0,
        //                                                                 .layerCount = VK_REMAINING_ARRAY_LAYERS};
        // vkCmdPipelineBarrier(pCommandBuffer->getCommandBufferHandle(), VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        //                      VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, 0, 0, nullptr, 0, nullptr, 1, &imageMemoryBarrier);
        VkResult acquireNextImageResult = vkAcquireNextImageKHR(this->pLogicalDevice->getLogicalDeviceHandle(), this->hSwapchain, UINT64_MAX,
                                                                this->upImageReadySemaphores.at(this->currentImageIndex)->getSemaphoreHandle(),
                                                                pFence != nullptr ? pFence->getFenceHandle() : VK_NULL_HANDLE, &swapchainImageIndex);
        // this->upPresentReadySemaphores[this->currentImageIndex] = std::move(std::make_unique<Semaphore>(this->pLogicalDevice));
        if (acquireNextImageResult == VK_ERROR_OUT_OF_DATE_KHR) {
            return {.outOfDate = true, .index = 0, .pImage = nullptr, .pSemaphoreImageReady = nullptr};
        }
        if (acquireNextImageResult != VK_SUCCESS && acquireNextImageResult != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("Failed to acquire next swapchain image");
        }

        this->upSwapchainImages[this->currentImageIndex] =
            std::move(std::make_unique<Image>(this->pLogicalDevice, this, this->hSwapchainImages.at(swapchainImageIndex)));
        SwapchainImage returnImage = {.outOfDate = false,
                                      .index = swapchainImageIndex,
                                      .pImage = this->upSwapchainImages.at(this->currentImageIndex).get(),
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