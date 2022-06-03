
// fillcan
#include <fillcan/shader/descriptor_set_layout.hpp>
#include <fillcan/shader/shader_module.hpp>

// std
#include <iostream>
#include <string>

namespace fillcan {
    ShaderModule::ShaderModule(std::string code, std::vector<std::unique_ptr<DescriptorSetLayout>> upDescriptorSetLayouts,
                               std::unique_ptr<DescriptorPool> upDescriptorPool /*, TODO: pushConstants*/)
        : upDescriptorSetLayouts(upDescriptorSetLayouts), upDescriptorPool(std::move(upDescriptorPool)) {}
    ShaderModule::~ShaderModule() {}

    VkShaderModule ShaderModule::getShaderModuleHandle() { return this->hShaderModule; }
    const std::vector<std::unique_ptr<DescriptorSetLayout>>& ShaderModule::getDescriptorSetLayouts() const { return this->upDescriptorSetLayouts; }
    const DescriptorPool* ShaderModule::getDescriptorPool() const { return this->upDescriptorPool.get(); }
} // namespace fillcan