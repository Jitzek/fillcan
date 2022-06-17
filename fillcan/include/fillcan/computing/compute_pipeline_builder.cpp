// fillcan
#include <fillcan/computing/compute_pipeline.hpp>
#include <fillcan/computing/compute_pipeline_builder.hpp>
#include <fillcan/shader/pipeline_builder.hpp>

// std
#include <memory>
#include <stdexcept>
#include <vector>

namespace fillcan {
    ComputePipelineBuilder::ComputePipelineBuilder() : PipelineBuilder() {}
    ComputePipelineBuilder::~ComputePipelineBuilder() { PipelineBuilder::~PipelineBuilder(); }

    void ComputePipelineBuilder::setShaderStage(PipelineShaderStage pipelineShaderStage) { this->pipelineShaderStage = pipelineShaderStage; }

    void ComputePipelineBuilder::reset() {
        PipelineBuilder::reset();
        this->pipelineShaderStage = {};
    }

    std::unique_ptr<ComputePipeline> ComputePipelineBuilder::getResult() {
        return std::move(std::make_unique<ComputePipeline>(this->pLogicalDevice, this->pCommandBuffer, this->flags,
                                                           std::vector<PipelineShaderStage>(1, this->pipelineShaderStage), std::move(this->pushConstants),
                                                           this->pipelineCache, this->pBasePipeline));
    }
} // namespace fillcan