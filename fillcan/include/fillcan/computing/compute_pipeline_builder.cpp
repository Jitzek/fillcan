#include "fillcan/computing/compute_pipeline.hpp"
#include "fillcan/shader/pipeline_builder.hpp"
#include <fillcan/computing/compute_pipeline_builder.hpp>
#include <stdexcept>
#include <vector>

namespace fillcan {
    ComputePipelineBuilder::ComputePipelineBuilder() : PipelineBuilder() {}
    ComputePipelineBuilder::~ComputePipelineBuilder() { PipelineBuilder::~PipelineBuilder(); }

    void ComputePipelineBuilder::setShaderStage(PipelineShaderStage pipelineShaderStage) { this->pipelineShaderStage = pipelineShaderStage; }

    void ComputePipelineBuilder::reset() {
        PipelineBuilder::reset();
        this->pipelineShaderStage.reset();
    }

    ComputePipeline ComputePipelineBuilder::getResult() { return ComputePipeline(this->pLogicalDevice, this->flags, {pipelineShaderStage.value()}); }
} // namespace fillcan