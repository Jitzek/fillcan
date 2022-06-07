// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/memory/image_view.hpp>
#include <fillcan/shader/descriptor_set.hpp>
#include <fillcan/shader/descriptor_set_layout.hpp>

// std
#include <vector>

namespace fillcan {
    DescriptorSet::DescriptorSet(LogicalDevice* pLogicalDevice, VkDescriptorSet hDescriptorSet, DescriptorSetLayout* pDescriptorSetLayout)
        : pLogicalDevice(pLogicalDevice), hDescriptorSet(hDescriptorSet), pDescriptorSetLayout(pDescriptorSetLayout) {}

    DescriptorSet::~DescriptorSet() {}

    VkDescriptorSet DescriptorSet::getDescriptorSetHandle() { return this->hDescriptorSet; }
    DescriptorSetLayout* DescriptorSet::getLayout() { return this->pDescriptorSetLayout; }

    void DescriptorSet::update(VkWriteDescriptorSet* pWrite, VkCopyDescriptorSet* pCopy) {
        vkUpdateDescriptorSets(this->pLogicalDevice->getLogicalDeviceHandle(), pWrite != nullptr ? 1 : 0, pWrite, pCopy != nullptr ? 1 : 0, pCopy);
    }

    void DescriptorSet::write(VkDescriptorSetLayoutBinding binding, VkDescriptorImageInfo* pImageInfo, VkDescriptorBufferInfo* pBufferInfo,
                              VkBufferView* pTexelBufferView) {
        VkWriteDescriptorSet writeDescriptorSet = {};
        writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        writeDescriptorSet.pNext = nullptr;
        writeDescriptorSet.dstSet = this->hDescriptorSet;
        writeDescriptorSet.dstBinding = binding.binding;
        writeDescriptorSet.dstArrayElement = 0;
        writeDescriptorSet.descriptorCount = 1;
        writeDescriptorSet.descriptorType = binding.descriptorType;
        writeDescriptorSet.pImageInfo = pImageInfo;
        writeDescriptorSet.pBufferInfo = pBufferInfo;
        writeDescriptorSet.pTexelBufferView = pTexelBufferView;
        this->update(&writeDescriptorSet, nullptr);
    }

    void DescriptorSet::writeImage(VkDescriptorSetLayoutBinding binding, ImageView* pImageView, VkImageLayout imageLayout) {
        VkDescriptorImageInfo descriptorImageInfo = {};
        descriptorImageInfo.sampler = VK_NULL_HANDLE;
        descriptorImageInfo.imageView = pImageView->getImageViewHandle();
        descriptorImageInfo.imageLayout = imageLayout;
        this->write(binding, &descriptorImageInfo, nullptr, nullptr);
    }
} // namespace fillcan