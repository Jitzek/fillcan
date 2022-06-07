#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

namespace fillcan {
    class LogicalDevice;
    class Buffer;
    class BufferView {
      private:
        VkBufferView hBufferView;
        LogicalDevice* pLogicalDevice;
        VkFormat format;
        VkDeviceSize offset;
        VkDeviceSize range;

      public:
        BufferView(LogicalDevice* pLogicalDevice, Buffer* pBuffer, VkFormat format, VkDeviceSize offset = 0, VkDeviceSize range = VK_WHOLE_SIZE);
        ~BufferView();

        VkBufferView getBufferViewHandle();
    };
} // namespace fillcan