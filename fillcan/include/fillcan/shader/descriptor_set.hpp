#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan

// std

namespace fillcan {
    class LogicalDevice;
    class DescriptorSetLayout;
    class ImageView;
    class Buffer;
    class BufferView;
    class DescriptorSet {
      private:
        VkDescriptorSet hDescriptorSet;
        LogicalDevice* pLogicalDevice;
        DescriptorSetLayout* pDescriptorSetLayout;

        void update(VkWriteDescriptorSet* pWrite, VkCopyDescriptorSet* pCopy);

        void write(VkDescriptorSetLayoutBinding binding, VkDescriptorImageInfo* pImageInfo, VkDescriptorBufferInfo* pBufferInfo,
                   VkBufferView* pTexelBufferView);

      public:
        DescriptorSet(LogicalDevice* pLogicalDevice, VkDescriptorSet hDescriptorSet, DescriptorSetLayout* pDescriptorSetLayout);
        ~DescriptorSet();

        VkDescriptorSet getDescriptorSetHandle();
        DescriptorSetLayout* getLayout();
        void writeImage(VkDescriptorSetLayoutBinding binding, ImageView* pImageView, VkImageLayout imageLayout /* TODO: Sampler */);
        void writeBuffer(VkDescriptorSetLayoutBinding binding, Buffer* pBuffer, VkDeviceSize offset = 0, VkDeviceSize range = VK_WHOLE_SIZE);
        void writeTexelBufferView(VkDescriptorSetLayoutBinding binding, BufferView* pTexelBufferView);
        void copy(VkDescriptorSetLayoutBinding srcDescriptorSetBinding, DescriptorSet* pDstDescriptorSet,
                  VkDescriptorSetLayoutBinding dstDescriptorSetBinding);
    };
} // namespace fillcan