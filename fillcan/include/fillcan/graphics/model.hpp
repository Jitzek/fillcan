#pragma once

// vulkan
#include "vulkan/vulkan_core.h"

// fillcan
#include <fillcan/memory/buffer.hpp>

// std
#include <memory>
#include <vector>

// glm
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace fillcan {
    class LogicalDevice;
    class CommandBuffer;
    class Model {
      private:
        LogicalDevice* pLogicalDevice;
        std::unique_ptr<Buffer> upVertexBuffer;
        uint32_t vertexCount;
        std::unique_ptr<Memory> upVertexMemory;

        std::unique_ptr<Buffer> upIndexBuffer;
        uint32_t indexCount;
        std::unique_ptr<Memory> upIndexMemory;
        
        CommandBuffer* pCommandBuffer = nullptr;

      public:
        struct Vertex {
            glm::vec3 position;
            glm::vec3 color;

            static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
            static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
        };

        Model(LogicalDevice* pLogicalDevice, const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices);
        ~Model();

        Model(const Model&) = delete;
        Model& operator=(const Model&) = delete;

        void bind(CommandBuffer* pCommandBuffer);
        void draw();
        void drawIndexed();
    };

} // namespace fillcan