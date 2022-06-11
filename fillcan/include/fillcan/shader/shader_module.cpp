
// fillcan
#include "fillcan/instance/logical_device.hpp"
#include <fillcan/shader/descriptor_set_layout.hpp>
#include <fillcan/shader/shader_module.hpp>

// std
#include <algorithm>
#include <iostream>
#include <string>

namespace fillcan {
    ShaderModule::ShaderModule(LogicalDevice* pLogicalDevice, std::vector<char>& code,
                               std::vector<std::unique_ptr<DescriptorSetLayout>> upDescriptorSetLayouts,
                               std::unique_ptr<DescriptorPool> upDescriptorPool /*, TODO: pushConstants*/)
        : pLogicalDevice(pLogicalDevice), upDescriptorSetLayouts(std::move(upDescriptorSetLayouts)), upDescriptorPool(std::move(upDescriptorPool)) {
        VkShaderModuleCreateInfo shaderModuleCreateInfo = {};
        shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        shaderModuleCreateInfo.pNext = nullptr;
        shaderModuleCreateInfo.flags = 0;
        shaderModuleCreateInfo.codeSize = code.size();
        shaderModuleCreateInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());
        if (vkCreateShaderModule(this->pLogicalDevice->getLogicalDeviceHandle(), &shaderModuleCreateInfo, nullptr, &this->hShaderModule) !=
            VK_SUCCESS) {
            throw std::runtime_error("Failed to create shader module");
        }
    }
    ShaderModule::~ShaderModule() {}

    VkShaderModule ShaderModule::getShaderModuleHandle() { return this->hShaderModule; }
    std::vector<DescriptorSetLayout*> ShaderModule::getDescriptorSetLayouts() {
        std::vector<DescriptorSetLayout*> pDescriptorSetLayouts = {};
        pDescriptorSetLayouts.reserve(this->upDescriptorSetLayouts.size());
        std::transform(this->upDescriptorSetLayouts.begin(), this->upDescriptorSetLayouts.end(), std::back_inserter(pDescriptorSetLayouts),
                       [](const std::unique_ptr<DescriptorSetLayout>& upDescriptorSetLayout) { return upDescriptorSetLayout.get(); });
        return pDescriptorSetLayouts;
    }
    DescriptorPool* ShaderModule::getDescriptorPool() const { return this->upDescriptorPool.get(); }
} // namespace fillcan