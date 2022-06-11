#pragma once

#include "vulkan/vulkan_core.h"
namespace fillcan {
    class LogicalDevice;
    class Pipeline;
    class PipelineBuilder {
      protected:
        LogicalDevice* pLogicalDevice = nullptr;
        VkPipelineCreateFlags flags = 0;
        Pipeline* pBasePipeline = nullptr;

      public:
        PipelineBuilder();
        virtual ~PipelineBuilder();
        virtual void setLogicalDevice(LogicalDevice* pLogicalDevice);
        virtual void setFlags(VkPipelineCreateFlags flags);
        virtual void setBasePipeline(Pipeline* pBasePipeline);
        virtual void reset();
    };
} // namespace fillcan