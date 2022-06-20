
// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include "fillcan/shader/descriptor_pool.hpp"
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/shader/descriptor_pool_builder.hpp>
#include <fillcan/shader/descriptor_set_layout.hpp>

// std
#include <memory>
#include <vector>

namespace fillcan {
    DescriptorPoolBuilder::DescriptorPoolBuilder() {}
    DescriptorPoolBuilder::~DescriptorPoolBuilder() {}

    void DescriptorPoolBuilder::setLogicalDevice(LogicalDevice* pLogicalDevice) { this->pLogicalDevice = pLogicalDevice; }

    void DescriptorPoolBuilder::setFlags(VkDescriptorPoolCreateFlags flags) { this->flags = flags; }

    void DescriptorPoolBuilder::addSet(DescriptorSetLayout* pDescriptorSetLayout, unsigned int amount) {
        this->pDescriptorSetLayouts.push_back(pDescriptorSetLayout);
        maxSets += amount;
        for (VkDescriptorSetLayoutBinding binding : pDescriptorSetLayout->getBindings()) {
            VkDescriptorPoolSize newdescriptorPoolSize = {.type = binding.descriptorType, .descriptorCount = binding.descriptorCount * amount};
            bool exists = false;
            for (VkDescriptorPoolSize& descriptorPoolSize : this->descriptorPoolSizes) {
                if (descriptorPoolSize.type == newdescriptorPoolSize.type) {
                    descriptorPoolSize.descriptorCount += newdescriptorPoolSize.descriptorCount;
                    exists = true;
                    break;
                }
            }
            if (!exists) {
                this->descriptorPoolSizes.push_back(newdescriptorPoolSize);
            }
        }
    }

    void DescriptorPoolBuilder::addSet(DescriptorSetLayout* pDescriptorSetLayout, std::string name) {
        this->pDescriptorSetLayouts.push_back(pDescriptorSetLayout);
        maxSets++;
        for (VkDescriptorSetLayoutBinding binding : pDescriptorSetLayout->getBindings()) {
            VkDescriptorPoolSize newdescriptorPoolSize = {.type = binding.descriptorType, .descriptorCount = binding.descriptorCount};
            bool exists = false;
            for (DescriptorSetInfo& descriptorSetInfo : this->descriptorSetInfos) {
                if (descriptorSetInfo.poolSize.type == newdescriptorPoolSize.type) {
                    descriptorSetInfo.poolSize.descriptorCount += newdescriptorPoolSize.descriptorCount;
                    descriptorSetInfo.names.push_back(name);
                    exists = true;
                    break;
                }
            }
            if (!exists) {
                this->descriptorSetInfos.push_back({newdescriptorPoolSize, pDescriptorSetLayout, {name}});
            }
        }
    }

    void DescriptorPoolBuilder::reset() {
        this->pLogicalDevice = nullptr;
        this->flags = 0;
        this->maxSets = 0;
        this->pDescriptorSetLayouts.clear();
        this->descriptorPoolSizes.clear();
    }

    std::unique_ptr<DescriptorPool> DescriptorPoolBuilder::getResult() {
        // std::unique_ptr<DescriptorPool> upDescriptorPool =
        //     std::make_unique<DescriptorPool>(this->pLogicalDevice, this->flags, this->maxSets, this->descriptorPoolSizes);
        // upDescriptorPool->allocateDescriptorSets(this->pDescriptorSetLayouts);
        // return std::move(upDescriptorPool);

        std::vector<VkDescriptorPoolSize> poolSizes = {};
        unsigned int maxSets = 0;
        for (DescriptorSetInfo descriptorSetInfo : this->descriptorSetInfos) {
            poolSizes.push_back(descriptorSetInfo.poolSize);
            maxSets += descriptorSetInfo.poolSize.descriptorCount;
        }
        std::unique_ptr<DescriptorPool> upDescriptorPool = std::make_unique<DescriptorPool>(this->pLogicalDevice, this->flags, maxSets, poolSizes);

        for (DescriptorSetInfo descriptorSetInfo : this->descriptorSetInfos) {
            for (std::string name : descriptorSetInfo.names) {
                upDescriptorPool->allocateDescriptorSet(descriptorSetInfo.pLayout, name);
            }
        }
        return std::move(upDescriptorPool);
    }
} // namespace fillcan