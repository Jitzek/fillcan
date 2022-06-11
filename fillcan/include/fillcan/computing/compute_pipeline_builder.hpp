#pragma once

// fillcan
#include "fillcan/shader/pipeline_builder.hpp"
#include <fillcan/shader/pipeline.hpp>

// std
#include <optional>
namespace fillcan {
    class ComputePipeline;
    class ComputePipelineBuilder : public PipelineBuilder {
      private:
        std::optional<PipelineShaderStage> pipelineShaderStage;

      public:
        ComputePipelineBuilder();
        ~ComputePipelineBuilder();

        void setShaderStage(PipelineShaderStage pipelineShaderStage);

        void reset() override;

        std::unique_ptr<ComputePipeline> getResult();
    };
} // namespace fillcan