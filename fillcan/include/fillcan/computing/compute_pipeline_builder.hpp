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
        /**
         * @brief Create a new Compute Pipeline Builder.
         *
         * @details The Compute Pipeline Builder class is part of the creational design pattern to construct complex objects step by step.
         * The Builder pattern allows you to produce different types and representations of an object using the same construction code.
         */
        ComputePipelineBuilder();
        ~ComputePipelineBuilder();

        /**
         * @brief Set the pipeline shader stage for the compute pipeline.
         * @see Pipeline#PipelineShaderStage
         *
         * @param pipelineShaderStage The pipeline shader stage.
         */
        void setShaderStage(PipelineShaderStage pipelineShaderStage);

        /**
         * @brief Get the resulting Compute Pipeline.
         *
         * @return A unique pointer to the Compute Pipeline, it's ownership will be moved.
         */
        std::unique_ptr<ComputePipeline> getResult();

        /**
         * @brief Reset the Builder to it's default values.
         */
        void reset() override;
    };
} // namespace fillcan