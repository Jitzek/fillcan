// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/shader/descriptor_set_layout.hpp>

// std
#include <stdexcept>
#include <vector>

namespace fillcan {
    DescriptorSetLayout::DescriptorSetLayout(LogicalDevice* pLogicalDevice, std::vector<VkDescriptorSetLayoutBinding> bindings)
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
        if (this->pLogicalDevice == nullptr) {
            std::cerr << "Failed to destroy Descriptor Set Layout: Logical Device was NULL"
                      << "\n";
        }
        if (this->hDescriptorSetLayout == VK_NULL_HANDLE) {
            std::cerr << "Failed to destroy Descriptor Set Layout: Handle was VK_NULL_HANDLE"
                      << "\n";
        }
        vkDestroyDescriptorSetLayout(this->pLogicalDevice->getLogicalDeviceHandle(), this->hDescriptorSetLayout, nullptr);
    }

    const VkDescriptorSetLayout DescriptorSetLayout::getDescriptorSetLayoutHandle() const { return this->hDescriptorSetLayout; }

    const std::vector<VkDescriptorSetLayoutBinding>& DescriptorSetLayout::getBindings() const { return this->bindings; }
} // namespace fillcan