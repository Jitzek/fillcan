// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/memory/image.hpp>
#include <fillcan/memory/image_view.hpp>

// std
#include <stdexcept>

namespace fillcan {
    ImageView::ImageView(LogicalDevice* pLogicalDevice, Image* pImage, VkImageViewType viewType, VkFormat format,
                         VkImageSubresourceRange subresourceRange, VkComponentMapping components)
        : pLogicalDevice(pLogicalDevice), viewType(viewType), format(format), subresourceRange(subresourceRange), components(components) {
        VkImageViewCreateInfo imageViewCreateInfo = {};
        imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        imageViewCreateInfo.pNext = nullptr;
        imageViewCreateInfo.flags = 0;
        imageViewCreateInfo.image = pImage->getImageHandle();
        imageViewCreateInfo.viewType = this->viewType;
        imageViewCreateInfo.format = this->format;
        imageViewCreateInfo.components = this->components;
        imageViewCreateInfo.subresourceRange = this->subresourceRange;
        if (vkCreateImageView(this->pLogicalDevice->getLogicalDeviceHandle(), &imageViewCreateInfo, nullptr, &this->hImageView) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create image view");
        }
    }
    ImageView::~ImageView() { vkDestroyImageView(this->pLogicalDevice->getLogicalDeviceHandle(), this->hImageView, nullptr); }

    VkImageView ImageView::getImageViewHandle() { return this->hImageView; }
} // namespace fillcan