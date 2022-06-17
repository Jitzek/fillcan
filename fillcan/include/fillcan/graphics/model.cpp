// fillcan
#include "vulkan/vulkan_core.h"
#include <fillcan/commands/command_buffer.hpp>
#include <fillcan/graphics/model.hpp>
#include <fillcan/memory/buffer.hpp>
#include <fillcan/memory/buffer_director.hpp>
#include <fillcan/memory/memory.hpp>

// std
#include <cstring>
#include <iostream>
#include <memory>
#include <vector>

namespace fillcan {
    Model::Model(LogicalDevice* pLogicalDevice, const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices)
        : pLogicalDevice(pLogicalDevice) {
        this->vertexCount = static_cast<uint32_t>(vertices.size());
        this->indexCount = static_cast<uint32_t>(indices.size());

        BufferDirector bufferDirector{};
        this->upVertexBuffer = bufferDirector.makeVertexBuffer(this->pLogicalDevice, sizeof(vertices[0]) * vertices.size());

        this->upVertexMemory = std::make_unique<Memory>(this->pLogicalDevice, upVertexBuffer.get(), VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
        this->upVertexBuffer->bindMemory(this->upVertexMemory.get());
        void** ppVertexData = this->upVertexBuffer->getMemory()->map();
        memcpy(*ppVertexData, vertices.data(), upVertexBuffer->getSize());
        this->upVertexBuffer->getMemory()->unmap();

        if (indices.size() > 0) {
            this->upIndexBuffer = bufferDirector.makeIndexBuffer(this->pLogicalDevice, sizeof(indices[0]) * indices.size());
            this->upIndexMemory = std::make_unique<Memory>(this->pLogicalDevice, upIndexBuffer.get(), VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
            this->upIndexBuffer->bindMemory(this->upIndexMemory.get());
            void** ppIndexData = this->upIndexBuffer->getMemory()->map();
            memcpy(*ppIndexData, indices.data(), upIndexBuffer->getSize());
            this->upIndexBuffer->getMemory()->unmap();
        }
    }

    Model::~Model() {}

    void Model::bind(CommandBuffer* pCommandBuffer) {
        VkBuffer hVertexBuffers[] = {upVertexBuffer->getBufferHandle()};
        VkDeviceSize offsets[] = {0};
        vkCmdBindVertexBuffers(pCommandBuffer->getCommandBufferHandle(), 0, 1, hVertexBuffers, offsets);
        if (this->upIndexBuffer != nullptr) {
            vkCmdBindIndexBuffer(pCommandBuffer->getCommandBufferHandle(), upIndexBuffer->getBufferHandle(), 0, VK_INDEX_TYPE_UINT16);
        }
        this->pCommandBuffer = pCommandBuffer;
    }

    void Model::draw() {
        if (this->pCommandBuffer == nullptr) {
            throw std::runtime_error("Model was not bound to a command buffer before drawing.");
        }
        vkCmdDraw(this->pCommandBuffer->getCommandBufferHandle(), this->vertexCount, 1, 0, 0);
    }

    void Model::drawIndexed() {
        if (this->pCommandBuffer == nullptr) {
            throw std::runtime_error("Model was not bound to a command buffer before drawing.");
        }
        vkCmdDrawIndexed(this->pCommandBuffer->getCommandBufferHandle(), this->indexCount, 1, 0, 0, 0);
    }

    std::vector<VkVertexInputBindingDescription> Model::Vertex::getBindingDescriptions() {
        return {{.binding = 0, .stride = sizeof(Vertex), .inputRate = VK_VERTEX_INPUT_RATE_VERTEX}};
    }

    std::vector<VkVertexInputAttributeDescription> Model::Vertex::getAttributeDescriptions() {
        return {{.location = 0, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = offsetof(Vertex, position)},
                {.location = 1, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = offsetof(Vertex, color)}};
    }
} // namespace fillcan