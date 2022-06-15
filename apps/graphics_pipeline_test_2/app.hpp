#pragma once

// fillcan
#include <fillcan/fillcan_graphics.hpp>
#include <fillcan/graphics/graphics_pipeline.hpp>
#include <fillcan/commands/command_buffer.hpp>

// std
#include <chrono>
#include <memory>
#include <vector>

namespace app_graphics_pipeline_test_2 {
    class App {
      private:
        std::unique_ptr<fillcan::FillcanGraphics> upFillcan = nullptr;
        std::unique_ptr<fillcan::GraphicsPipeline> upGraphicsPipeline = nullptr;
        std::unique_ptr<fillcan::Buffer> upVertexBuffer = nullptr;
        std::unique_ptr<fillcan::Buffer> upIndexBuffer = nullptr;
        std::vector<fillcan::CommandBuffer*> pGraphicsCommandBuffers = {};
        uint32_t currentFrameIndex = 0;

        void createSwapchain();
        void createRenderPass();
        void createGraphicsPipeline(fillcan::ShaderModule* pVertexShaderModule, fillcan::ShaderModule* pFragmentShaderModule);
      public:
        App();
        ~App();
        void run();
        void update(/*std::chrono::duration<double> deltaTime*/);
    };
} // namespace app_graphics_pipeline_test_2