#pragma once

// fillcan
#include <fillcan/commands/command_buffer.hpp>
#include <fillcan/fillcan.hpp>

#include <fillcan/shader/descriptor_pool.hpp>
#include <fillcan/shader/descriptor_set_layout.hpp>

#include <fillcan/computing/compute_pipeline.hpp>

#include <fillcan/memory/fence.hpp>

// std
#include <memory>
#include <vector>

namespace app_compute_pipeline_test {
    class DescriptorSetLayout;
    class App {
      private:
        std::unique_ptr<fillcan::Fillcan> upFillcan;

      public:
        App();
        ~App();
        void run();
        void update();

        std::vector<std::unique_ptr<fillcan::DescriptorSetLayout>> createDescriptorSetLayouts();
        std::unique_ptr<fillcan::DescriptorPool>
        createDescriptorPool(std::vector<std::unique_ptr<fillcan::DescriptorSetLayout>>& upDescriptorSetLayouts);
        std::unique_ptr<fillcan::ComputePipeline> createComputePipeline(fillcan::PipelineShaderStage pipelineShaderStage);
    };
} // namespace app_compute_pipeline_test