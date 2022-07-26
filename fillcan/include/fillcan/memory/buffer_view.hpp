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
        /**
         * @brief Create a new Buffer View
         *
         * @details The Buffer View class takes a pointer to a Logical Device, a pointer to the parent Buffer which it will create a Buffer View for,
         * along with information regarding the format and size of the Buffer View. A Buffer View is used to interpret the data in a Buffer with a
         * specific format. Buffer Views represent a sub-scope of a buffer object. Since the raw data in the Buffer is then treated as a sequence of
         * texels, this is also known as a texel buffer view. A texel buffer view is directly accessible in shaders and Vulkan will automatically
         * convert the texels in the Buffer to the format expected by the shader.
         *
         * @param pLogicalDevice A pointer to the Logical Device the Buffer View should be associated with.
         * @param pBuffer A pointer to the parent Buffer to create a Buffer View of.
         * @param format When bound as a texel buffer, the data in the Buffer is interpreted as a string of texels with the format specified in this
         * field.
         * The specified format must support VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT, VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT or
         * VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT, as reported by PhysicalDevice#getFormatProperties.
         * @param offset The new view will be a "window" in the parent Buffer, starting from offset bytes. The number of bytes of the Buffer where the
         * Buffer View should start. To create a Buffer View of the entire Buffer, this must be 0.
         * @param range The new view will be a "window" in the parent Buffer, expanding to range bytes. The number of bytes the Buffer View
         * will contain from offset. To create a Buffer View of the entire Buffer, it must be VK_WHOLE_SIZE.
         * The maximum number of texels that can be stored in a texel buffer is determined by inspecting the maxTexelBufferElements field of the
         * device's VkPhysicalDeviceLimits-structure, which can be retrieved by calling PhysicalDevice#getProperties. If the buffer is used as a texel
         * buffer, the range divided by the size of a texel in format field must be less than or equal to this limit. maxTexelBufferElements is
         * guaranteed to be a minimum of 65,536, so if the view being created contains fewer texels, this limit does not need to be requested.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPhysicalDeviceLimits.html
         *
         * @throws std::runtime_error if the Vulkan Buffer View couldn't be created.
         * @see https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkBufferView.html
         */
        BufferView(LogicalDevice* pLogicalDevice, Buffer* pBuffer, VkFormat format, VkDeviceSize offset = 0, VkDeviceSize range = VK_WHOLE_SIZE);
        ~BufferView();
        BufferView(const BufferView&) = delete;
        BufferView& operator=(const BufferView&) = delete;

        /**
         * @brief Get the handle to the Vulkan Buffer View.
         *
         * @return The handle to the Vulkan Buffer View.
         */
        const VkBufferView getBufferViewHandle() const;
    };
} // namespace fillcan