// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/shader/descriptor_pool.hpp>
#include <fillcan/shader/descriptor_set_layout.hpp>

// std
#include <memory>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <cstddef>

namespace fillcan {
    DescriptorPool::DescriptorPool(LogicalDevice* pLogicalDevice, VkDescriptorPoolCreateFlags flags, unsigned int maxSets,
                                   std::vector<VkDescriptorPoolSize> poolSizes)
        : pLogicalDevice(pLogicalDevice), flags(flags), maxSets(maxSets), poolSizes(poolSizes) {
        VkDescriptorPoolCreateInfo descriptorPoolCreateInfo = {};
        descriptorPoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        descriptorPoolCreateInfo.pNext = nullptr;
        descriptorPoolCreateInfo.flags = flags;
        descriptorPoolCreateInfo.maxSets = maxSets;
        descriptorPoolCreateInfo.poolSizeCount = poolSizes.size();
        descriptorPoolCreateInfo.pPoolSizes = poolSizes.data();
        if (vkCreateDescriptorPool(this->pLogicalDevice->getLogicalDeviceHandle(), &descriptorPoolCreateInfo, nullptr, &this->hDescriptorPool) !=
            VK_SUCCESS) {
            throw std::runtime_error("Failed to create descriptor pool");
        }
    }

    DescriptorPool::~DescriptorPool() { vkDestroyDescriptorPool(this->pLogicalDevice->getLogicalDeviceHandle(), this->hDescriptorPool, nullptr); }

    bool DescriptorPool::allocateDescriptorSets(std::vector<DescriptorSetLayout*> pDescriptorSetLayouts) {
        std::vector<VkDescriptorSetLayout> descriptorSetLayoutsHandles = {};
        for (DescriptorSetLayout* pDescriptorSetLayout : pDescriptorSetLayouts) {
            descriptorSetLayoutsHandles.push_back(pDescriptorSetLayout->getDescriptorSetLayoutHandle());
        }

        VkDescriptorSetAllocateInfo descriptorSetAllocateInfo = {};
        descriptorSetAllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        descriptorSetAllocateInfo.pNext = nullptr;
        descriptorSetAllocateInfo.descriptorPool = this->hDescriptorPool;
        descriptorSetAllocateInfo.descriptorSetCount = descriptorSetLayoutsHandles.size();
        descriptorSetAllocateInfo.pSetLayouts = descriptorSetLayoutsHandles.data();

        std::vector<VkDescriptorSet> descriptorSetsHandles(descriptorSetLayoutsHandles.size());
        if (vkAllocateDescriptorSets(this->pLogicalDevice->getLogicalDeviceHandle(), &descriptorSetAllocateInfo, descriptorSetsHandles.data()) !=
            VK_SUCCESS) {
            return false;
        }
        this->upDescriptorSets.reserve(descriptorSetsHandles.size());
        for (int i = 0; i < descriptorSetsHandles.size(); i++) {
            this->upDescriptorSets.push_back(
                std::make_unique<DescriptorSet>(this->pLogicalDevice, descriptorSetsHandles[i], pDescriptorSetLayouts[i]));
        }
        return true;
    }

    VkDescriptorPool DescriptorPool::getDescriptorPoolHandle() { return this->hDescriptorPool; }

    std::vector<DescriptorSet*> DescriptorPool::getDescriptorSets() {
        std::vector<DescriptorSet*> pDescriptorSets = {};
        std::transform(this->upDescriptorSets.begin(), this->upDescriptorSets.end(), std::back_inserter(pDescriptorSets),
                       [](const std::unique_ptr<DescriptorSet>& upDescriptorSet) { return upDescriptorSet.get(); });
        return pDescriptorSets;
    }

    bool DescriptorPool::freeDescriptorSets(std::vector<DescriptorSet*> pDescriptorSets) {
        if (!(this->flags & VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT)) {
            return false;
        }
        std::vector<VkDescriptorSet> descriptorSetsHandles = {};
        descriptorSetsHandles.reserve(pDescriptorSets.size());
        for (DescriptorSet* pDescriptorSet : pDescriptorSets) {
            descriptorSetsHandles.push_back(pDescriptorSet->getDescriptorSetHandle());
        }
        return vkFreeDescriptorSets(this->pLogicalDevice->getLogicalDeviceHandle(), this->hDescriptorPool, descriptorSetsHandles.size(),
                                    descriptorSetsHandles.data()) == VK_SUCCESS
                   ? true
                   : false;
    }

    bool DescriptorPool::freeDescriptorSets() {
        if (!(this->flags & VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT)) {
            return false;
        }
        std::vector<VkDescriptorSet> descriptorSetsHandles = {};
        descriptorSetsHandles.reserve(this->upDescriptorSets.size());
        for (std::unique_ptr<DescriptorSet>& upDescriptorSet : this->upDescriptorSets) {
            descriptorSetsHandles.push_back(upDescriptorSet->getDescriptorSetHandle());
        }
        return vkFreeDescriptorSets(this->pLogicalDevice->getLogicalDeviceHandle(), this->hDescriptorPool, descriptorSetsHandles.size(),
                                    descriptorSetsHandles.data()) == VK_SUCCESS
                   ? true
                   : false;
    }

    bool DescriptorPool::reset() {
        return vkResetDescriptorPool(this->pLogicalDevice->getLogicalDeviceHandle(), this->hDescriptorPool, 0) == VK_SUCCESS ? true : false;
    }
} // namespace fillcan