#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan

// std
#include <memory>
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class DescriptorSetLayout;
    class DescriptorSetLayoutBuilder {
      private:
        LogicalDevice* pLogicalDevice = nullptr;
        std::vector<VkDescriptorSetLayoutBinding> bindings = {};

      public:
        DescriptorSetLayoutBuilder();
        ~DescriptorSetLayoutBuilder();

        void setLogicalDevice(LogicalDevice* pLogicalDevice);
        void addBinding(unsigned int binding, VkDescriptorType descriptorType, unsigned int descriptorCount, VkShaderStageFlags stageFlags,
                        std::vector<VkSampler> immutableSamplers = {});

        std::unique_ptr<DescriptorSetLayout> getResult();
        void reset();
    };
} // namespace fillcan