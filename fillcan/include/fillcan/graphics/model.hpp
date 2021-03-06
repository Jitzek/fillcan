#pragma once

// vulkan
#include "glm/detail/type_vec.hpp"
#include "vulkan/vulkan_core.h"

// fillcan
#include <cstddef>
#include <fillcan/commands/command_recording.hpp>
#include <fillcan/graphics/texture.hpp>
#include <fillcan/memory/buffer.hpp>

// std
#include <functional>
#include <memory>
#include <string>
#include <vector>

// glm
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace fillcan {
    class LogicalDevice;
    class CommandBuffer;
    class Model {
      public:
        struct Vertex {
            glm::vec3 position{};
            glm::vec3 color{};
            glm::vec2 textureCoordinate{};
            glm::vec3 normal{};

            bool operator==(const Vertex& other) const {
                return position == other.position && color == other.color && textureCoordinate == other.textureCoordinate && normal == other.normal;
            }

            static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
            static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
            static VkVertexInputAttributeDescription getPositionAttributeDescription(unsigned int location, unsigned int binding = 0);
            static VkVertexInputAttributeDescription getColorAttributeDescription(unsigned int location, unsigned int binding = 0);
            static VkVertexInputAttributeDescription getTextureCoordinateAttributeDescription(unsigned int location, unsigned int binding = 0);
            static VkVertexInputAttributeDescription getNormalAttributeDescription(unsigned int location, unsigned int binding = 0);
        };

      private:
        LogicalDevice* pLogicalDevice;
        std::unique_ptr<Buffer> upVertexBuffer;
        uint32_t vertexCount;
        std::unique_ptr<Memory> upVertexMemory;

        std::unique_ptr<Buffer> upIndexBuffer;
        uint32_t indexCount;
        std::unique_ptr<Memory> upIndexMemory;

        Texture* pTexture = nullptr;

        CommandBuffer* pCommandBuffer = nullptr;

        void init(const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices);

        void createVertexBuffer(const std::vector<Vertex>& vertices);
        void createIndexBuffer(const std::vector<uint16_t>& indices);

      public:
        Model(LogicalDevice* pLogicalDevice, const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices);
        Model(LogicalDevice* pLogicalDevice, std::string filePath);
        ~Model();
        Model(const Model&) = delete;
        Model& operator=(const Model&) = delete;

        // void setTexture(Texture* pTexture);
        // Texture* getTexture();

        void bind(CommandBuffer* pCommandBuffer);
        void draw();
        void drawIndexed();

        Texture* texture = nullptr;
    };

} // namespace fillcan