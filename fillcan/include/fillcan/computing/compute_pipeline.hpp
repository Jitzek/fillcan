#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include "fillcan/shader/pipeline.hpp"

// std
#include <memory>

namespace fillcan {
    class LogicalDevice;
    class ComputePipeline : public Pipeline {
      private:
      public:
        ComputePipeline(LogicalDevice* pLogicalDevice, VkPipelineCreateFlags flags, std::vector<PipelineShaderStage> shaderStages,
                        VkPipelineCache pipelineCache = VK_NULL_HANDLE, Pipeline* pBasePipeline = nullptr);
        ~ComputePipeline();
    };
} // namespace fillcan