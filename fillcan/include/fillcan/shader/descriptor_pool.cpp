// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/shader/descriptor_pool.hpp>
#include <fillcan/shader/descriptor_set.hpp>
#include <fillcan/shader/descriptor_set_layout.hpp>

// std
#include <algorithm>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <vector>

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

    DescriptorPool::~DescriptorPool() {
        if (this->pLogicalDevice == nullptr) {
            std::cerr << "Failed to destroy Descriptor Pool: Logical Device was NULL"
                      << "\n";
        }
        if (this->hDescriptorPool == VK_NULL_HANDLE) {
            std::cerr << "Failed to destroy Descriptor Pool: Handle was VK_NULL_HANDLE"
                      << "\n";
        }
        vkDestroyDescriptorPool(this->pLogicalDevice->getLogicalDeviceHandle(), this->hDescriptorPool, nullptr);
    }

    bool DescriptorPool::allocateDescriptorSets(std::vector<DescriptorSetLayout*> pDescriptorSetLayouts) {
        std::vector<VkDescriptorSetLayout> descriptorSetLayoutsHandles = {};
        std::vector<DescriptorSetLayout*> _pDescriptorSetLayouts = {};
        for (size_t i = 0; i < pDescriptorSetLayouts.size(); i++) {
            for (size_t j = 0; j < this->poolSizes.at(i).descriptorCount; j++) {
                _pDescriptorSetLayouts.push_back(pDescriptorSetLayouts.at(i));
            }
        }
        pDescriptorSetLayouts = _pDescriptorSetLayouts;
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
        // for (DescriptorSetLayout* pDescriptorSetLayout : pDescriptorSetLayouts) {
        //     for (size_t i = 0; i < pDescriptorSetLayout->getBindings().size(); i++) {
        //         if (this->poolSizes.at(i).type == pDescriptorSetLayout->getBindings().at(i).descriptorType) {
        //             for (size_t j = 0; j < this->poolSizes.at(i).descriptorCount; j++) {
        //                 this->upDescriptorSets.push_back(
        //                     std::make_unique<DescriptorSet>(this->pLogicalDevice, descriptorSetsHandles[i], pDescriptorSetLayouts[i]));
        //             }
        //         }
        //     }
        // }
        for (int i = 0; i < descriptorSetsHandles.size(); i++) {
            this->upDescriptorSets.push_back(
                std::make_unique<DescriptorSet>(this->pLogicalDevice, descriptorSetsHandles[i], pDescriptorSetLayouts[i]));
        }
        return true;
    }

    DescriptorSet* DescriptorPool::allocateDescriptorSet(DescriptorSetLayout* pDescriptorSetLayout, std::string name) {
        VkDescriptorSetAllocateInfo descriptorSetAllocateInfo = {};
        descriptorSetAllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        descriptorSetAllocateInfo.pNext = nullptr;
        descriptorSetAllocateInfo.descriptorPool = this->hDescriptorPool;
        descriptorSetAllocateInfo.descriptorSetCount = 1;
        std::vector<VkDescriptorSetLayout> hDescriptorSetLayouts = {pDescriptorSetLayout->getDescriptorSetLayoutHandle()};
        descriptorSetAllocateInfo.pSetLayouts = hDescriptorSetLayouts.data();

        VkDescriptorSet hDescriptorSet;
        if (vkAllocateDescriptorSets(this->pLogicalDevice->getLogicalDeviceHandle(), &descriptorSetAllocateInfo, &hDescriptorSet) != VK_SUCCESS) {
            throw std::runtime_error("Failed to allocated descriptor set");
        }
        this->upDescriptorSets.push_back(std::make_unique<DescriptorSet>(this->pLogicalDevice, hDescriptorSet, pDescriptorSetLayout, name));
        return this->upDescriptorSets.back().get();
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
        bool succesful = vkFreeDescriptorSets(this->pLogicalDevice->getLogicalDeviceHandle(), this->hDescriptorPool, descriptorSetsHandles.size(),
                                              descriptorSetsHandles.data()) == VK_SUCCESS
                             ? true
                             : false;

        for (DescriptorSet* pDescriptorSet : pDescriptorSets) {
            this->upDescriptorSets.erase(std::remove_if(
                this->upDescriptorSets.begin(), this->upDescriptorSets.end(),
                [pDescriptorSet](std::unique_ptr<DescriptorSet>& rupDescriptorSet) { return rupDescriptorSet.get() == pDescriptorSet; }));
        }
        return succesful;
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

    DescriptorSet* DescriptorPool::getDescriptorSet(std::string name) {
        for (std::unique_ptr<DescriptorSet>& upDescriptorSet : this->upDescriptorSets) {
            if (upDescriptorSet->getName() == name) {
                return upDescriptorSet.get();
            }
        }
        throw std::runtime_error("Failed to find descriptor set with name: \"" + name + "\"");
    }

    bool DescriptorPool::reset() {
        return vkResetDescriptorPool(this->pLogicalDevice->getLogicalDeviceHandle(), this->hDescriptorPool, 0) == VK_SUCCESS ? true : false;
    }
} // namespace fillcan