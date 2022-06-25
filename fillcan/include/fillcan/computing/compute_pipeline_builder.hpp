#pragma once

// fillcan
#include <fillcan/shader/pipeline.hpp>
#include <fillcan/shader/pipeline_builder.hpp>

// std
#include <memory>

namespace fillcan {
    class ComputePipeline;
    class ComputePipelineBuilder : public PipelineBuilder {
      private:
        PipelineShaderStage pipelineShaderStage = {};

      public:
        ComputePipelineBuilder();
        ~ComputePipelineBuilder();

        void setShaderStage(PipelineShaderStage pipelineShaderStage);

        void reset() override;

        std::unique_ptr<ComputePipeline> getResult();
    };
} // namespace fillcan