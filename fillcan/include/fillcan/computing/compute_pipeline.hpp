#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/shader/pipeline.hpp>
#include <fillcan/shader/pipeline_layout.hpp>

// std
#include <memory>

namespace fillcan {
    class LogicalDevice;
    class CommandBuffer;
    class ComputePipeline : public Pipeline {
      private:
      public:
        ComputePipeline(LogicalDevice* pLogicalDevice, VkPipelineCreateFlags flags, std::vector<PipelineShaderStage> shaderStages,
                        std::vector<PushConstant> pushConstants, VkPipelineCache pipelineCache = VK_NULL_HANDLE, Pipeline* pBasePipeline = nullptr);
        ~ComputePipeline();

        ComputePipeline(const ComputePipeline&) = delete;
        ComputePipeline& operator=(const ComputePipeline&) = delete;
    };
} // namespace fillcan