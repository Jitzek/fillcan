// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <cstdint>
#include <fillcan/commands/queue.hpp>
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/swapchain/swapchain.hpp>
#include <fillcan/window.hpp>
#include <stdexcept>
#include <vector>

namespace fillcan {
    Swapchain::Swapchain(LogicalDevice* pLogicalDevice, Window* pWindow, Queue* pPresentQueue, BufferMode bufferMode, VkPresentModeKHR presentMode,
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

        VkSwapchainCreateInfoKHR swapchainCreateInfo = {};
        swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        swapchainCreateInfo.pNext = nullptr;
        swapchainCreateInfo.flags = 0;
        swapchainCreateInfo.surface = this->pWindow->getSurface();
        swapchainCreateInfo.minImageCount = bufferMode;
        swapchainCreateInfo.imageFormat = this->surfaceFormat.format;
        swapchainCreateInfo.imageColorSpace = this->surfaceFormat.colorSpace;
        swapchainCreateInfo.imageExtent = this->pWindow->getExtent();
        swapchainCreateInfo.imageArrayLayers = 1;
        swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        swapchainCreateInfo.queueFamilyIndexCount = 0;
        swapchainCreateInfo.pQueueFamilyIndices = nullptr;
        swapchainCreateInfo.preTransform = pLogicalDevice->getPhysicalDevice()->getSurfaceCapabilitiesKHR().currentTransform;
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
        this->hSwapchainImages.reserve(swapchainImageCount);
        if (vkGetSwapchainImagesKHR(this->pLogicalDevice->getLogicalDeviceHandle(), this->hSwapchain, &swapchainImageCount,
                                    this->hSwapchainImages.data()) != VK_SUCCESS) {
            throw std::runtime_error("Failed to get swapchain images");
        }
    }

    Swapchain::~Swapchain() {}

    VkSwapchainKHR Swapchain::getSwapchainHandle() { return this->hSwapchain; }

    SwapchainImage Swapchain::getNextImage(CommandBuffer* pCommandBuffer) {
        uint32_t imageIndex = 0;
        VkSemaphore hSemaphore = VK_NULL_HANDLE;

        if (pCommandBuffer != nullptr) {
            VkSemaphoreCreateInfo semaphoreCreateInfo = {};
            semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
            semaphoreCreateInfo.pNext = nullptr;
            semaphoreCreateInfo.flags = 0;
            if (vkCreateSemaphore(this->pLogicalDevice->getLogicalDeviceHandle(), &semaphoreCreateInfo, nullptr, &hSemaphore) != VK_SUCCESS) {
                throw std::runtime_error("Failed to create semphore needed for acquiring the next swapchain image");
            }
            VkImageMemoryBarrier imageMemoryBarrier = {};
            imageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
            imageMemoryBarrier.pNext = nullptr;
            imageMemoryBarrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
            imageMemoryBarrier.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
            imageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
            imageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
            imageMemoryBarrier.srcQueueFamilyIndex = 0;
            imageMemoryBarrier.dstQueueFamilyIndex = 0;
            imageMemoryBarrier.image = this->hSwapchainImages[imageIndex];
            imageMemoryBarrier.subresourceRange = (VkImageSubresourceRange){.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                                                                            .baseMipLevel = 0,
                                                                            .levelCount = VK_REMAINING_MIP_LEVELS,
                                                                            .baseArrayLayer = 0,
                                                                            .layerCount = VK_REMAINING_ARRAY_LAYERS};
            vkCmdPipelineBarrier(pCommandBuffer->getCommandBufferHandle(), VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                                 VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, 0, 0, nullptr, 0, nullptr, 1, &imageMemoryBarrier);
        }
        VkResult acquireNextImageResult = vkAcquireNextImageKHR(this->pLogicalDevice->getLogicalDeviceHandle(), this->hSwapchain, UINT64_MAX,
                                                                hSemaphore, VK_NULL_HANDLE, &imageIndex);
        if (acquireNextImageResult == VK_ERROR_OUT_OF_DATE_KHR) {
            return (SwapchainImage){.outOfDate = true, .index = 0, .hImage = nullptr, .hSemaphore = nullptr};
        }
        if (acquireNextImageResult != VK_SUCCESS) {
            throw std::runtime_error("Failed to acquire next swapchain image");
        }

        return (SwapchainImage){.outOfDate = false, .index = imageIndex, .hImage = this->hSwapchainImages[imageIndex], .hSemaphore = hSemaphore};
    }

    VkSurfaceFormatKHR Swapchain::getSurfaceFormat() { return this->surfaceFormat; }

    void Swapchain::present(SwapchainImage& swapchainImage, VkSemaphore* pSemaphore) {}
} // namespace fillcan