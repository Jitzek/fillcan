#pragma once

// vulkan
#include "vulkan/vulkan_core.h"
#include <string>

// fillcan

// std

namespace fillcan {
    class LogicalDevice;
    class DescriptorSetLayout;
    class ImageView;
    class Buffer;
    class BufferView;
    class Sampler;
    class DescriptorSet {
      private:
        VkDescriptorSet hDescriptorSet;
        LogicalDevice* pLogicalDevice;
        DescriptorSetLayout* pDescriptorSetLayout;
        std::string name = "Undefined";

        void update(VkWriteDescriptorSet* pWrite, VkCopyDescriptorSet* pCopy);

      public:
        DescriptorSet(LogicalDevice* pLogicalDevice, VkDescriptorSet hDescriptorSet, DescriptorSetLayout* pDescriptorSetLayout);
        DescriptorSet(LogicalDevice* pLogicalDevice, VkDescriptorSet hDescriptorSet, DescriptorSetLayout* pDescriptorSetLayout, std::string name);
        ~DescriptorSet();

        VkDescriptorSet getDescriptorSetHandle();

        DescriptorSetLayout* getLayout();
        std::string getName();

        void write(VkDescriptorSetLayoutBinding binding, VkDescriptorImageInfo* pImageInfo, VkDescriptorBufferInfo* pBufferInfo,
                   VkBufferView* pTexelBufferView, unsigned int dstArrayElement = 0, unsigned int descriptorCount = 1);
        void writeImage(VkDescriptorSetLayoutBinding binding, ImageView* pImageView, VkImageLayout imageLayout, Sampler* pSampler);
        void writeBuffer(VkDescriptorSetLayoutBinding binding, Buffer* pBuffer, VkDeviceSize offset = 0, VkDeviceSize range = VK_WHOLE_SIZE);
        void writeTexelBufferView(VkDescriptorSetLayoutBinding binding, BufferView* pTexelBufferView);
        void copy(VkDescriptorSetLayoutBinding srcDescriptorSetBinding, DescriptorSet* pDstDescriptorSet,
                  VkDescriptorSetLayoutBinding dstDescriptorSetBinding);
    };
} // namespace fillcan