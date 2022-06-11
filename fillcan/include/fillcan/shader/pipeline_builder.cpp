
// fillcan
#include "fillcan/commands/command_buffer.hpp"
#include "vulkan/vulkan_core.h"
#include <fillcan/shader/pipeline_builder.hpp>

namespace fillcan {
    PipelineBuilder::PipelineBuilder() {}
    PipelineBuilder::~PipelineBuilder() {}

    void PipelineBuilder::setLogicalDevice(LogicalDevice* pLogicalDevice) { this->pLogicalDevice = pLogicalDevice; }

    void PipelineBuilder::setCommandBuffer(CommandBuffer* pCommandBuffer) { this->pCommandBuffer = pCommandBuffer; }

    void PipelineBuilder::setFlags(VkPipelineCreateFlags flags) { this->flags = flags; }

    void PipelineBuilder::setPipelineCache(VkPipelineCache pipelineCache) { this->pipelineCache = pipelineCache; }

    void PipelineBuilder::setBasePipeline(Pipeline* pBasePipeline) { this->pBasePipeline = pBasePipeline; }

    void PipelineBuilder::reset() {
        this->pLogicalDevice = nullptr;
        this->pCommandBuffer = nullptr;
        this->flags = 0;
        this->pipelineCache = VK_NULL_HANDLE;
        this->pBasePipeline = nullptr;
    }
} // namespace fillcan