// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/memory/buffer.hpp>
#include <fillcan/memory/buffer_view.hpp>
#include <stdexcept>

namespace fillcan {
    BufferView::BufferView(LogicalDevice* pLogicalDevice, Buffer* pBuffer, VkFormat format, VkDeviceSize offset, VkDeviceSize range)
        : pLogicalDevice(pLogicalDevice), format(format), offset(offset), range(range) {
        VkBufferViewCreateInfo bufferViewCreateInfo = {};
        bufferViewCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO;
        bufferViewCreateInfo.pNext = nullptr;
        bufferViewCreateInfo.flags = 0;
        bufferViewCreateInfo.buffer = pBuffer->getBufferHandle();
        bufferViewCreateInfo.format = format;
        bufferViewCreateInfo.offset = offset;
        bufferViewCreateInfo.range = range;
        if (vkCreateBufferView(this->pLogicalDevice->getLogicalDeviceHandle(), &bufferViewCreateInfo, nullptr, &this->hBufferView) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create buffer view");
        }
    }
    BufferView::~BufferView() {
        if (this->pLogicalDevice == nullptr) {
            std::cerr << "Failed to destroy Buffer View: Logical Device was NULL"
                      << "\n";
        }
        if (this->hBufferView == VK_NULL_HANDLE) {
            std::cerr << "Failed to destroy Buffer View: Handle was VK_NULL_HANDLE"
                      << "\n";
        }
        vkDestroyBufferView(this->pLogicalDevice->getLogicalDeviceHandle(), this->hBufferView, nullptr);
    }

    VkBufferView BufferView::getBufferViewHandle() { return this->hBufferView; }
} // namespace fillcan