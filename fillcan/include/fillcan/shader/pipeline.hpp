#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/shader/pipeline_layout.hpp>

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
        Pipeline(LogicalDevice* pLogicalDevice, CommandBuffer* pCommandBuffer, VkPipelineCreateFlags flags,
                 std::vector<PipelineShaderStage> shaderStages, std::vector<PushConstant> pushConstants,
                 VkPipelineCache pipelineCache = VK_NULL_HANDLE, Pipeline* pBasePipeline = nullptr);
        virtual ~Pipeline();

        Pipeline(const Pipeline&) = delete;
        Pipeline& operator=(const Pipeline&) = delete;

        VkPipeline getPipelineHandle();

        PipelineLayout* getPipelineLayout();
        void bindToCommandBuffer(CommandBuffer* pCommandBuffer);
        void bindDescriptorSets();
        void bindDescriptorSets(std::vector<DescriptorSet*> pDescriptorSets, unsigned int firstSet);
        void bindDescriptorSets(std::vector<std::string> names, unsigned int firstSet);
        std::vector<DescriptorSet*>& getDescriptorSets();
        CommandBuffer* getCommandBuffer();

        DescriptorSet* getDescriptorSet(std::string name);

        void start();
    };
} // namespace fillcan