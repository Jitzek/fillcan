#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// std
#include <memory>
#include <string>
#include <vector>

namespace fillcan {
    class CommandBuffer;
    class LogicalDevice;
    class PipelineLayout;
    class ShaderModule;
    class DescriptorSetLayout;
    class DescriptorSet;

    struct PipelineShaderStage {
        VkShaderStageFlagBits stage;
        ShaderModule* pShaderModule;
        std::string name;
        // TODO: Specialization Constants
    };

    class Pipeline {
      protected:
        VkPipeline hPipeline;
        LogicalDevice* pLogicalDevice;
        VkPipelineCreateFlags flags;
        std::vector<PipelineShaderStage> shaderStages;
        std::vector<DescriptorSetLayout*> pDescriptorSetLayouts = {};
        std::vector<DescriptorSet*> pDescriptorSets = {};
        std::unique_ptr<PipelineLayout> layout;
        CommandBuffer* pCommandBuffer = nullptr;
        VkPipelineBindPoint bindPoint = VK_PIPELINE_BIND_POINT_MAX_ENUM;

      protected:
        void setBindPoint(VkPipelineBindPoint pipelineBindPoint);

      public:
        Pipeline(LogicalDevice* pLogicalDevice, CommandBuffer* pCommandBuffer, VkPipelineCreateFlags flags, std::vector<PipelineShaderStage> shaderStages,
                 VkPipelineCache pipelineCache = VK_NULL_HANDLE, Pipeline* pBasePipeline = nullptr);
        virtual ~Pipeline();

        VkPipeline getPipelineHandle();

        PipelineLayout* getPipelineLayout();
        void bindToCommandBuffer(CommandBuffer* pCommandBuffer);
        void bindDescriptorSets();
        CommandBuffer* getCommandBuffer();

        void start();
    };
} // namespace fillcan