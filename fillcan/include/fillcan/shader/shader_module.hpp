#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include "fillcan/shader/descriptor_pool.hpp"
#include "fillcan/shader/descriptor_set_layout.hpp"
#include <fillcan/shader/descriptor_set_layout_builder.hpp>

// std
#include <memory>
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class ShaderModule {
      private:
        VkShaderModule hShaderModule;
        LogicalDevice* pLogicalDevice;
        std::vector<std::unique_ptr<DescriptorSetLayout>> upDescriptorSetLayouts = {};
        std::unique_ptr<DescriptorPool> upDescriptorPool = nullptr;
        // TODO: pushconstants
      public:
        ShaderModule(LogicalDevice* pLogicalDevice, std::vector<char>& code, std::vector<std::unique_ptr<DescriptorSetLayout>> upDescriptorSetLayouts,
                     std::unique_ptr<DescriptorPool> upDescriptorPool);
        ShaderModule(LogicalDevice* pLogicalDevice, std::vector<uint32_t>& code,
                     std::vector<std::unique_ptr<DescriptorSetLayout>> upDescriptorSetLayouts, std::unique_ptr<DescriptorPool> upDescriptorPool);
        ~ShaderModule();

        VkShaderModule getShaderModuleHandle();
        std::vector<DescriptorSetLayout*> getDescriptorSetLayouts();
        DescriptorPool* getDescriptorPool() const;
    };
} // namespace fillcan