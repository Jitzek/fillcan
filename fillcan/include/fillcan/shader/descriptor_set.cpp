// vulkan
#include "fillcan/graphics/sampler.hpp"
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/memory/buffer.hpp>
#include <fillcan/memory/buffer_view.hpp>
#include <fillcan/memory/image_view.hpp>
#include <fillcan/shader/descriptor_set.hpp>
#include <fillcan/shader/descriptor_set_layout.hpp>

// std
#include <string>
#include <vector>

namespace fillcan {
    DescriptorSet::DescriptorSet(LogicalDevice* pLogicalDevice, VkDescriptorSet hDescriptorSet, DescriptorSetLayout* pDescriptorSetLayout)
        : pLogicalDevice(pLogicalDevice), hDescriptorSet(hDescriptorSet), pDescriptorSetLayout(pDescriptorSetLayout) {}

    DescriptorSet::DescriptorSet(LogicalDevice* pLogicalDevice, VkDescriptorSet hDescriptorSet, DescriptorSetLayout* pDescriptorSetLayout,
                                 std::string name)
        : pLogicalDevice(pLogicalDevice), hDescriptorSet(hDescriptorSet), pDescriptorSetLayout(pDescriptorSetLayout), name(name) {}

    DescriptorSet::~DescriptorSet() {}

    VkDescriptorSet DescriptorSet::getDescriptorSetHandle() { return this->hDescriptorSet; }

    DescriptorSetLayout* DescriptorSet::getLayout() { return this->pDescriptorSetLayout; }

    std::string DescriptorSet::getName() { return this->name; }

    void DescriptorSet::update(VkWriteDescriptorSet* pWrite, VkCopyDescriptorSet* pCopy) {
        vkUpdateDescriptorSets(this->pLogicalDevice->getLogicalDeviceHandle(), pWrite != nullptr ? 1 : 0, pWrite, pCopy != nullptr ? 1 : 0, pCopy);
    }

    void DescriptorSet::write(VkDescriptorSetLayoutBinding binding, VkDescriptorImageInfo* pImageInfo, VkDescriptorBufferInfo* pBufferInfo,
                              VkBufferView* pTexelBufferView, unsigned int dstArrayElement, unsigned int descriptorCount) {
        VkWriteDescriptorSet writeDescriptorSet = {};
        writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        writeDescriptorSet.pNext = nullptr;
        writeDescriptorSet.dstSet = this->hDescriptorSet;
        writeDescriptorSet.dstBinding = binding.binding;
        writeDescriptorSet.dstArrayElement = dstArrayElement;
        writeDescriptorSet.descriptorCount = descriptorCount;
        writeDescriptorSet.descriptorType = binding.descriptorType;
        writeDescriptorSet.pImageInfo = pImageInfo;
        writeDescriptorSet.pBufferInfo = pBufferInfo;
        writeDescriptorSet.pTexelBufferView = pTexelBufferView;
        this->update(&writeDescriptorSet, nullptr);
    }

    void DescriptorSet::writeImage(VkDescriptorSetLayoutBinding binding, ImageView* pImageView, VkImageLayout imageLayout, Sampler* pSampler) {
        VkDescriptorImageInfo descriptorImageInfo = {};
        descriptorImageInfo.sampler = pSampler->getSamplerHandle();
        descriptorImageInfo.imageView = pImageView->getImageViewHandle();
        descriptorImageInfo.imageLayout = imageLayout;
        this->write(binding, &descriptorImageInfo, nullptr, nullptr);
    }

    void DescriptorSet::writeBuffer(VkDescriptorSetLayoutBinding binding, Buffer* pBuffer, VkDeviceSize offset, VkDeviceSize range) {
        VkDescriptorBufferInfo descriptorBufferInfo = {};
        descriptorBufferInfo.buffer = pBuffer->getBufferHandle();
        descriptorBufferInfo.offset = offset;
        descriptorBufferInfo.range = range;
        this->write(binding, nullptr, &descriptorBufferInfo, nullptr);
    }

    void DescriptorSet::writeTexelBufferView(VkDescriptorSetLayoutBinding binding, BufferView* pTexelBufferView) {
        VkBufferView hTexelBufferViews[1] = {pTexelBufferView->getBufferViewHandle()};
        this->write(binding, nullptr, nullptr, hTexelBufferViews);
    }

    void DescriptorSet::copy(VkDescriptorSetLayoutBinding srcDescriptorSetBinding, DescriptorSet* pDstDescriptorSet,
                             VkDescriptorSetLayoutBinding dstDescriptorSetBinding) {
        VkCopyDescriptorSet copyDescriptorSet = {};
        copyDescriptorSet.sType = VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET;
        copyDescriptorSet.pNext = nullptr;
        copyDescriptorSet.srcSet = this->hDescriptorSet;
        copyDescriptorSet.srcBinding = srcDescriptorSetBinding.binding;
        copyDescriptorSet.srcArrayElement = 0;
        copyDescriptorSet.dstSet = pDstDescriptorSet->getDescriptorSetHandle();
        copyDescriptorSet.dstBinding = dstDescriptorSetBinding.binding;
        copyDescriptorSet.dstArrayElement = 0;
        copyDescriptorSet.descriptorCount = 1;
        this->update(nullptr, &copyDescriptorSet);
    }
} // namespace fillcan