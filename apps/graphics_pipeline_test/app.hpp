#pragma once

// fillcan
#include "fillcan/graphics/render_pass.hpp"
#include "fillcan/shader/shader_module.hpp"
#include <fillcan/commands/command_buffer.hpp>
#include <fillcan/fillcan_graphics.hpp>

#include <fillcan/shader/descriptor_pool.hpp>
#include <fillcan/shader/descriptor_set_layout.hpp>

#include <fillcan/graphics/graphics_pipeline.hpp>

// std
#include <memory>
#include <vector>

namespace app_graphics_pipeline_test {
    class DescriptorSetLayout;
    class App {
      private:
        std::unique_ptr<fillcan::FillcanGraphics> upFillcan;
        std::unique_ptr<fillcan::GraphicsPipeline> upGraphicsPipeline;

      public:
        App();
        ~App();
        void run();
        void update();

        void createRenderPass();
        std::vector<std::unique_ptr<fillcan::DescriptorSetLayout>> createDescriptorSetLayouts();

        std::unique_ptr<fillcan::DescriptorPool>
        createDescriptorPool(std::vector<std::unique_ptr<fillcan::DescriptorSetLayout>>& upDescriptorSetLayouts);

        void createGraphicsPipeline(fillcan::CommandBuffer* pCommandBuffer, fillcan::ShaderModule* pVertexShaderModule,
                                    fillcan::ShaderModule* pFragmentShaderModule);
    };
} // namespace app_graphics_pipeline_test