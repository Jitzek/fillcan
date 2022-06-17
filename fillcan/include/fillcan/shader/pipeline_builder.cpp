
// fillcan
#include "fillcan/commands/command_buffer.hpp"
#include "vulkan/vulkan_core.h"
#include <fillcan/shader/pipeline_builder.hpp>

namespace fillcan {
    PipelineBuilder::PipelineBuilder() {}
    PipelineBuilder::~PipelineBuilder() {}

    void PipelineBuilder::setLogicalDevice(LogicalDevice* pLogicalDevice) { this->pLogicalDevice = pLogicalDevice; }

    void PipelineBuilder::setFlags(VkPipelineCreateFlags flags) { this->flags = flags; }

    void PipelineBuilder::addPushConstant(std::string name, VkPushConstantRange pushConstantRange) {
        this->pushConstants.push_back({.name = name, .range = pushConstantRange, .data = {}});
    }

    void PipelineBuilder::setPipelineCache(VkPipelineCache pipelineCache) { this->pipelineCache = pipelineCache; }

    void PipelineBuilder::setBasePipeline(Pipeline* pBasePipeline) { this->pBasePipeline = pBasePipeline; }

    void PipelineBuilder::reset() {
        this->pLogicalDevice = nullptr;
        this->pCommandBuffer = nullptr;
        this->flags = 0;
        this->pushConstants.clear();
        this->pipelineCache = VK_NULL_HANDLE;
        this->pBasePipeline = nullptr;
    }
} // namespace fillcan