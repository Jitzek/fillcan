
// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/commands/command_buffer.hpp>
#include <fillcan/shader/pipeline_builder.hpp>
#include <fillcan/shader/pipeline_layout.hpp>

// std
#include <memory>

namespace fillcan {
    PipelineBuilder::PipelineBuilder() {}
    PipelineBuilder::~PipelineBuilder() {}

    void PipelineBuilder::setLogicalDevice(LogicalDevice* pLogicalDevice) { this->pLogicalDevice = pLogicalDevice; }

    void PipelineBuilder::setFlags(VkPipelineCreateFlags flags) { this->flags = flags; }

    void PipelineBuilder::addPushConstant(std::string name, VkPushConstantRange pushConstantRange) {
        PushConstant pushConstant = {.name = name, .range = pushConstantRange, .upData = std::make_unique<PushConstantData>()};
        this->pushConstants.push_back(std::move(pushConstant));
    }

    void PipelineBuilder::setPipelineCache(VkPipelineCache pipelineCache) { this->pipelineCache = pipelineCache; }

    void PipelineBuilder::setBasePipeline(Pipeline* pBasePipeline) { this->pBasePipeline = pBasePipeline; }

    void PipelineBuilder::reset() {
        this->pLogicalDevice = nullptr;
        this->flags = 0;
        this->pushConstants.clear();
        this->pipelineCache = VK_NULL_HANDLE;
        this->pBasePipeline = nullptr;
    }
} // namespace fillcan