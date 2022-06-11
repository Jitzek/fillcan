
// fillcan
#include <fillcan/shader/pipeline_builder.hpp>

namespace fillcan {
    PipelineBuilder::PipelineBuilder() {}
    PipelineBuilder::~PipelineBuilder() {}

    void PipelineBuilder::setLogicalDevice(LogicalDevice* pLogicalDevice) { this->pLogicalDevice = pLogicalDevice; }

    void PipelineBuilder::setFlags(VkPipelineCreateFlags flags) { this->flags = flags; }

    void PipelineBuilder::setBasePipeline(Pipeline* pBasePipeline) { this->pBasePipeline = pBasePipeline; }

    void PipelineBuilder::reset() {
        this->pLogicalDevice = nullptr;
        this->flags = 0;
        this->pBasePipeline = nullptr;
    }
} // namespace fillcan