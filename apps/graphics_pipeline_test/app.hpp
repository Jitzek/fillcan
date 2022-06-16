#pragma once

// fillcan
#include "fillcan/commands/command_recording.hpp"
#include "fillcan/graphics/framebuffer.hpp"
#include "fillcan/graphics/render_pass.hpp"
#include "fillcan/shader/shader_module.hpp"
#include <fillcan/commands/command_buffer.hpp>
#include <fillcan/fillcan_graphics.hpp>

#include <fillcan/shader/descriptor_pool.hpp>
#include <fillcan/shader/descriptor_set_layout.hpp>

#include <fillcan/graphics/graphics_pipeline.hpp>

#include <fillcan/memory/fence.hpp>

// std
#include <chrono>
#include <memory>
#include <vector>

// glm
#include <glm/detail/type_vec.hpp>
#include <glm/glm.hpp>

namespace app_graphics_pipeline_test {
    class DescriptorSetLayout;

    struct Vertex {
        glm::vec3 position;
        glm::vec3 color;
    };
    class App {
      private:
        std::unique_ptr<fillcan::FillcanGraphics> upFillcan;
        std::unique_ptr<fillcan::GraphicsPipeline> upGraphicsPipeline;
        std::unique_ptr<fillcan::Buffer> upVertexBuffer = nullptr;
        std::unique_ptr<fillcan::Buffer> upIndexBuffer = nullptr;

        std::vector<std::unique_ptr<fillcan::Semaphore>> upSemaphores;
        // std::vector<std::unique_ptr<fillcan::Fence>> upFrameFences;
        std::unique_ptr<fillcan::Semaphore> upGraphicsSemaphore;
        std::vector<fillcan::CommandRecording*> pCommandRecordings;
        std::vector<std::unique_ptr<fillcan::Framebuffer>> upFramebuffers;

        uint32_t currentFrameIndex = 0;

        std::vector<Vertex> vertices = {
            {{0.0f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}}, {{0.5f, 0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}}, {{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}}};

        const std::vector<uint16_t> indices = {0, 1, 2};

        void** ppVertexData = nullptr;
        void** ppIndexData = nullptr;

      public:
        App();
        ~App();
        void run();
        void update(double deltaTime);

        void createRenderPass();
        std::vector<std::unique_ptr<fillcan::DescriptorSetLayout>> createDescriptorSetLayouts();

        std::unique_ptr<fillcan::DescriptorPool>
        createDescriptorPool(std::vector<std::unique_ptr<fillcan::DescriptorSetLayout>>& upDescriptorSetLayouts);

        void createGraphicsPipeline(fillcan::ShaderModule* pVertexShaderModule, fillcan::ShaderModule* pFragmentShaderModule);
    };
} // namespace app_graphics_pipeline_test