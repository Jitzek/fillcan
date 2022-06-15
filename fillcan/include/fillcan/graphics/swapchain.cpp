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
#include <memory>
#include <stdexcept>
#include <utility>
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
        this->hSwapchainImages.resize(swapchainImageCount);
        if (vkGetSwapchainImagesKHR(this->pLogicalDevice->getLogicalDeviceHandle(), this->hSwapchain, &swapchainImageCount,
                                    this->hSwapchainImages.data()) != VK_SUCCESS) {
            throw std::runtime_error("Failed to get swapchain images");
        }
        // for (VkImage hSwapchainImage : hSwapchainImages) {
        //     this->upSwapchainImages.push_back(std::move(std::make_unique<Image>(this->pLogicalDevice, this, hSwapchainImage)));
        // }
        this->upSwapchainImages.resize(this->hSwapchainImages.size());
        this->upSemaphores.resize(this->hSwapchainImages.size());
    }

    Swapchain::~Swapchain() { vkDestroySwapchainKHR(this->pLogicalDevice->getLogicalDeviceHandle(), this->hSwapchain, nullptr); }

    VkSwapchainKHR Swapchain::getSwapchainHandle() { return this->hSwapchain; }

    BufferMode Swapchain::getBufferMode() { return this->bufferMode; }

    unsigned int Swapchain::getImageArrayLayers() { return this->imageArrayLayers; }

    VkImageUsageFlags Swapchain::getImageUsage() { return this->imageUsage; }

    VkSharingMode Swapchain::getImageSharingMode() { return this->imageSharingMode; }

    std::vector<uint32_t>& Swapchain::getQueueFamilyIndices() { return this->queueFamilyIndices; }

    SwapchainImage Swapchain::getNextImage() {
        uint32_t imageIndex = 0;
        std::unique_ptr<Semaphore> upSemaphore = std::make_unique<Semaphore>(this->pLogicalDevice);

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
                                                                upSemaphore->getSemaphoreHandle(), VK_NULL_HANDLE, &imageIndex);
        this->upSemaphores[imageIndex] = std::move(upSemaphore);
        if (acquireNextImageResult == VK_ERROR_OUT_OF_DATE_KHR || acquireNextImageResult == VK_SUBOPTIMAL_KHR) {
            return {.outOfDate = true, .index = 0, .pImage = nullptr, .pSemaphore = nullptr};
        }
        if (acquireNextImageResult != VK_SUCCESS) {
            throw std::runtime_error("Failed to acquire next swapchain image");
        }

        this->upSwapchainImages[imageIndex] = std::move(std::make_unique<Image>(this->pLogicalDevice, this, this->hSwapchainImages[imageIndex]));
        return (SwapchainImage){.outOfDate = false,
                                .index = imageIndex,
                                .pImage = this->upSwapchainImages[imageIndex].get(),
                                .pSemaphore = this->upSemaphores[imageIndex].get()};
    }

    VkSurfaceFormatKHR Swapchain::getSurfaceFormat() { return this->surfaceFormat; }

    void Swapchain::present(SwapchainImage* pSwapchainImage, std::vector<VkSemaphore> waitSemaphores) {
        if (pSwapchainImage == nullptr) {
            throw std::runtime_error("Failed to present swapchain image: Image was invalid");
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
            throw std::runtime_error("Failed to present swapchain image");
        }
    }

    VkExtent2D Swapchain::getImageExtent() { return this->pWindow->getExtent(); }
} // namespace fillcan