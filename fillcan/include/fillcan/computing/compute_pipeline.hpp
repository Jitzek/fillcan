#pragma once

// vulkan
#include "fillcan/shader/pipeline_layout.hpp"
#include "vulkan/vulkan_core.h"

// fillcan
#include "fillcan/shader/pipeline.hpp"

// std
#include <memory>

namespace fillcan {
    class LogicalDevice;
    class CommandBuffer;
    class ComputePipeline : public Pipeline {
      private:
      public:
        ComputePipeline(LogicalDevice* pLogicalDevice, CommandBuffer* pCommandBuffer, VkPipelineCreateFlags flags,
                        std::vector<PipelineShaderStage> shaderStages, std::vector<PushConstant> pushConstants, VkPipelineCache pipelineCache = VK_NULL_HANDLE,
                        Pipeline* pBasePipeline = nullptr);
        ~ComputePipeline();
    };
} // namespace fillcan