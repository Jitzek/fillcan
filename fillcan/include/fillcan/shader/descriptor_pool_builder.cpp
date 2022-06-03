
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
            std::pair<VkDescriptorType, unsigned int> newDescriptorAndCount = {binding.descriptorType, binding.descriptorCount * amount};
            bool exists = false;
            for (std::pair<VkDescriptorType, unsigned int>& descriptorAndCount : this->descriptorsAndCounts) {
                if (descriptorAndCount.first == newDescriptorAndCount.first) {
                    descriptorAndCount.second += newDescriptorAndCount.second;
                    exists = true;
                    break;
                }
            }
            if (!exists) {
                this->descriptorsAndCounts.push_back(newDescriptorAndCount);
            }
        }
        for (std::pair<VkDescriptorType, unsigned int> thing : this->descriptorsAndCounts) {
            std::cout << thing.first << " " << thing.second << "\n";
        }
    }

    std::unique_ptr<DescriptorPool> DescriptorPoolBuilder::getResult() {
        std::vector<VkDescriptorPoolSize> poolSizes = {};
        poolSizes.reserve(this->descriptorsAndCounts.size());
        for (std::pair<VkDescriptorType, unsigned int>& descriptorAndCount : this->descriptorsAndCounts) {
            poolSizes.emplace_back((VkDescriptorPoolSize){.type = descriptorAndCount.first, .descriptorCount = descriptorAndCount.second});
        }
        std::unique_ptr<DescriptorPool> upDescriptorPool =
            std::make_unique<DescriptorPool>(this->pLogicalDevice, this->flags, this->maxSets, poolSizes);
        upDescriptorPool->allocateDescriptorSets(this->pDescriptorSetLayouts);
        return std::move(upDescriptorPool);
    }
} // namespace fillcan