// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include "fillcan/instance/logical_device.hpp"
#include <fillcan/shader/descriptor_set_layout.hpp>

// std
#include <stdexcept>
#include <vector>

namespace fillcan {
    DescriptorSetLayout::DescriptorSetLayout(LogicalDevice* pLogicalDevice, std::vector<VkDescriptorSetLayoutBinding> bindings, unsigned int amount)
        : pLogicalDevice(pLogicalDevice), bindings(bindings) {
        VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo = {};
        descriptorSetLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        descriptorSetLayoutCreateInfo.pNext = nullptr;
        descriptorSetLayoutCreateInfo.flags = 0;
        descriptorSetLayoutCreateInfo.bindingCount = this->bindings.size();
        descriptorSetLayoutCreateInfo.pBindings = this->bindings.data();
        if (vkCreateDescriptorSetLayout(this->pLogicalDevice->getLogicalDeviceHandle(), &descriptorSetLayoutCreateInfo, nullptr,
                                        &this->hDescriptorSetLayout) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create descriptor set layout");
        }
    }

    DescriptorSetLayout::~DescriptorSetLayout() {
        vkDestroyDescriptorSetLayout(this->pLogicalDevice->getLogicalDeviceHandle(), this->hDescriptorSetLayout, nullptr);
    }

    VkDescriptorSetLayout DescriptorSetLayout::getDescriptorSetLayoutHandle() { return this->hDescriptorSetLayout; }

    const std::vector<VkDescriptorSetLayoutBinding>& DescriptorSetLayout::getBindings() const { return this->bindings; }
} // namespace fillcan