
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

    void DescriptorPoolBuilder::addSet(DescriptorSetLayout* pDescriptorSetLayout, std::string name) {
        this->pDescriptorSetLayouts.push_back(pDescriptorSetLayout);
        maxSets++;
        DescriptorSetInfo descriptorSetInfo = {.name = name, .pLayout = pDescriptorSetLayout, .poolSizes = {}};
        for (VkDescriptorSetLayoutBinding binding : pDescriptorSetLayout->getBindings()) {
            VkDescriptorPoolSize newdescriptorPoolSize = {.type = binding.descriptorType, .descriptorCount = binding.descriptorCount};
            bool exists = false;
            for (VkDescriptorPoolSize& descriptorPoolSize : descriptorSetInfo.poolSizes) {
                if (descriptorPoolSize.type == newdescriptorPoolSize.type) {
                    descriptorPoolSize.descriptorCount += newdescriptorPoolSize.descriptorCount;
                    exists = true;
                    break;
                }
            }
            if (!exists) {
                descriptorSetInfo.poolSizes.push_back(newdescriptorPoolSize);
            }
        }
        this->descriptorSetInfos.push_back(descriptorSetInfo);
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

        unsigned int maxSets = 0;
        std::vector<VkDescriptorPoolSize> poolSizes = {};
        for (DescriptorSetInfo& descriptorSetInfo : this->descriptorSetInfos) {
            for (VkDescriptorPoolSize& poolSize : descriptorSetInfo.poolSizes) {
                poolSizes.push_back(poolSize);
                maxSets += poolSize.descriptorCount;
            }
        }
        std::unique_ptr<DescriptorPool> upDescriptorPool = std::make_unique<DescriptorPool>(this->pLogicalDevice, this->flags, maxSets, poolSizes);

        for (DescriptorSetInfo descriptorSetInfo : this->descriptorSetInfos) {
            upDescriptorPool->allocateDescriptorSet(descriptorSetInfo.pLayout, descriptorSetInfo.name);
        }
        return std::move(upDescriptorPool);
    }
} // namespace fillcan