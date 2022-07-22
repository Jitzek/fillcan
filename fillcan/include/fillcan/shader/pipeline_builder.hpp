#pragma once
// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/shader/pipeline_layout.hpp>

// std
#include <string>
#include <vector>

namespace fillcan {
    class LogicalDevice;
    class Pipeline;
    class CommandBuffer;
    class PipelineBuilder {
      protected:
        LogicalDevice* pLogicalDevice = nullptr;
        VkPipelineCreateFlags flags = 0;
        std::vector<PushConstant> pushConstants = {};
        VkPipelineCache pipelineCache = VK_NULL_HANDLE;
        Pipeline* pBasePipeline = nullptr;

      public:
        PipelineBuilder();
        virtual ~PipelineBuilder();
        virtual void setLogicalDevice(LogicalDevice* pLogicalDevice);
        virtual void setFlags(VkPipelineCreateFlags flags);
        virtual void addPushConstant(std::string name, VkPushConstantRange pushConstantRange);
        virtual void setPipelineCache(VkPipelineCache pipelineCache);
        virtual void setBasePipeline(Pipeline* pBasePipeline);
        virtual void reset();
    };
} // namespace fillcan