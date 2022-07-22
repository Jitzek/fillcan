// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/graphics/sampler.hpp>
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/memory/buffer.hpp>
#include <fillcan/memory/buffer_view.hpp>
#include <fillcan/memory/image_view.hpp>
#include <fillcan/shader/descriptor_pool.hpp>
#include <fillcan/shader/descriptor_set.hpp>
#include <fillcan/shader/descriptor_set_layout.hpp>

// std
#include <string>
#include <vector>

namespace fillcan {
    DescriptorSet::DescriptorSet(LogicalDevice* pLogicalDevice, DescriptorPool* pDescriptorPool, DescriptorSetLayout* pDescriptorSetLayout,
                                 std::string name)
        : pLogicalDevice(pLogicalDevice), pDescriptorSetLayout(pDescriptorSetLayout), name(name) {
        VkDescriptorSetAllocateInfo descriptorSetAllocateInfo = {};
        descriptorSetAllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        descriptorSetAllocateInfo.pNext = nullptr;
        descriptorSetAllocateInfo.descriptorPool = pDescriptorPool->getDescriptorPoolHandle();
        descriptorSetAllocateInfo.descriptorSetCount = 1;
        std::vector<VkDescriptorSetLayout> hDescriptorSetLayouts = {pDescriptorSetLayout->getDescriptorSetLayoutHandle()};
        descriptorSetAllocateInfo.pSetLayouts = hDescriptorSetLayouts.data();

        if (vkAllocateDescriptorSets(this->pLogicalDevice->getLogicalDeviceHandle(), &descriptorSetAllocateInfo, &this->hDescriptorSet) !=
            VK_SUCCESS) {
            throw std::runtime_error("Failed to allocate descriptor set");
        }
    }

    DescriptorSet::~DescriptorSet() {}

    const VkDescriptorSet DescriptorSet::getDescriptorSetHandle() const { return this->hDescriptorSet; }

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

    void DescriptorSet::writeImage(VkDescriptorSetLayoutBinding binding, ImageView* pImageView, VkImageLayout imageLayout, Sampler* pSampler,
                                   unsigned int dstArrayElement, unsigned int descriptorCount) {
        VkDescriptorImageInfo descriptorImageInfo = {};
        descriptorImageInfo.sampler = pSampler->getSamplerHandle();
        descriptorImageInfo.imageView = pImageView->getImageViewHandle();
        descriptorImageInfo.imageLayout = imageLayout;
        this->write(binding, &descriptorImageInfo, nullptr, nullptr, dstArrayElement, descriptorCount);
    }

    void DescriptorSet::writeBuffer(VkDescriptorSetLayoutBinding binding, Buffer* pBuffer, VkDeviceSize offset, VkDeviceSize range,
                                    unsigned int dstArrayElement, unsigned int descriptorCount) {
        VkDescriptorBufferInfo descriptorBufferInfo = {};
        descriptorBufferInfo.buffer = pBuffer->getBufferHandle();
        descriptorBufferInfo.offset = offset;
        descriptorBufferInfo.range = range;
        this->write(binding, nullptr, &descriptorBufferInfo, nullptr, dstArrayElement, descriptorCount);
    }

    void DescriptorSet::writeTexelBufferView(VkDescriptorSetLayoutBinding binding, BufferView* pTexelBufferView, unsigned int dstArrayElement,
                                             unsigned int descriptorCount) {
        VkBufferView hTexelBufferViews[1] = {pTexelBufferView->getBufferViewHandle()};
        this->write(binding, nullptr, nullptr, hTexelBufferViews, dstArrayElement, descriptorCount);
    }

    void DescriptorSet::copy(VkDescriptorSetLayoutBinding srcDescriptorSetBinding, DescriptorSet* pDstDescriptorSet,
                             VkDescriptorSetLayoutBinding dstDescriptorSetBinding, unsigned int dstArrayElement, unsigned int descriptorCount) {
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