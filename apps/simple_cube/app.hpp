#pragma once

// fillcan
#include "fillcan/commands/command_recording.hpp"
#include "fillcan/graphics/framebuffer.hpp"
#include "fillcan/graphics/game_object.hpp"
#include "fillcan/graphics/render_pass.hpp"
#include "fillcan/shader/pipeline_layout.hpp"
#include "fillcan/shader/shader_module.hpp"
#include "glm/detail/type_mat.hpp"
#include <fillcan/commands/command_buffer.hpp>
#include <fillcan/fillcan_graphics.hpp>

#include <fillcan/shader/descriptor_pool.hpp>
#include <fillcan/shader/descriptor_set_layout.hpp>

#include <fillcan/graphics/graphics_pipeline.hpp>
#include <fillcan/graphics/model.hpp>

#include <fillcan/memory/fence.hpp>

// std
#include <chrono>
#include <memory>
#include <vector>

// glm
#include <glm/detail/type_vec.hpp>
#include <glm/glm.hpp>

namespace simple_cube {
    class DescriptorSetLayout;

    struct SimplePushConstantData : fillcan::PushConstantData {
        glm::mat4 transform{1.f};
        alignas(16) glm::vec3 color;
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

        std::string APP_DIR = "./apps/simple_cube";

        std::vector<fillcan::GameObject> gameObjects = {};
        std::vector<std::shared_ptr<fillcan::Model>> spModels = {};

        void loadGameObjects();
        void renderGameObjects(fillcan::CommandBuffer* pCommandBuffer);

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
} // namespace simple_cube