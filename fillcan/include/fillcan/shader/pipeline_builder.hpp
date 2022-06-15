#pragma once

#include "vulkan/vulkan_core.h"
namespace fillcan {
    class LogicalDevice;
    class Pipeline;
    class CommandBuffer;
    class PipelineBuilder {
      protected:
        LogicalDevice* pLogicalDevice = nullptr;
        CommandBuffer* pCommandBuffer = nullptr;
        VkPipelineCreateFlags flags = 0;
        VkPipelineCache pipelineCache = VK_NULL_HANDLE;
        Pipeline* pBasePipeline = nullptr;

      public:
        PipelineBuilder();
        virtual ~PipelineBuilder();
        virtual void setLogicalDevice(LogicalDevice* pLogicalDevice);
        virtual void setFlags(VkPipelineCreateFlags flags);
        virtual void setPipelineCache(VkPipelineCache pipelineCache);
        virtual void setBasePipeline(Pipeline* pBasePipeline);
        virtual void reset();
    };
} // namespace fillcan