// fillcan
#include "fillcan/shader/pipeline.hpp"
#include <fillcan/computing/compute_pipeline.hpp>

namespace fillcan {
    ComputePipeline::ComputePipeline(LogicalDevice* pLogicalDevice, VkPipelineCreateFlags flags, std::vector<PipelineShaderStage> shaderStages,
                                     VkPipelineCache pipelineCache, Pipeline* pBasePipeline)
        : Pipeline(pLogicalDevice, flags, shaderStages) {}

    ComputePipeline::~ComputePipeline() { Pipeline::~Pipeline(); }
} // namespace fillcan