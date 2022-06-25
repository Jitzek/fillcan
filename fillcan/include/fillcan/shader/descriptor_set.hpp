#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan

// std
#include <string>

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
        std::string name = "undefined";

        void update(VkWriteDescriptorSet* pWrite, VkCopyDescriptorSet* pCopy);

      public:
        DescriptorSet(LogicalDevice* pLogicalDevice, VkDescriptorSet hDescriptorSet, DescriptorSetLayout* pDescriptorSetLayout);
        DescriptorSet(LogicalDevice* pLogicalDevice, VkDescriptorSet hDescriptorSet, DescriptorSetLayout* pDescriptorSetLayout, std::string name);
        ~DescriptorSet();

        DescriptorSet(const DescriptorSet&) = delete;
        DescriptorSet& operator=(const DescriptorSet&) = delete;

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