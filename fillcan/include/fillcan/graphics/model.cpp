// fillcan
#include "fillcan/commands/command_recording.hpp"
#include "vulkan/vulkan_core.h"
#include <fillcan/commands/command_buffer.hpp>
#include <fillcan/commands/queue.hpp>
#include <fillcan/graphics/model.hpp>
#include <fillcan/instance/logical_device.hpp>
#include <fillcan/memory/buffer.hpp>
#include <fillcan/memory/buffer_director.hpp>
#include <fillcan/memory/memory.hpp>

// std
#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

// tinyobjloader
#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader/tiny_obj_loader.h>

namespace fillcan {
    Model::Model(LogicalDevice* pLogicalDevice, const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices)
        : pLogicalDevice(pLogicalDevice) {
        this->init(vertices, indices);
    }

    Model::Model(LogicalDevice* pLogicalDevice, std::string& filePath) : pLogicalDevice(pLogicalDevice) {
        std::vector<Vertex> vertices;
        std::vector<uint16_t> indices;

        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string warn, err;

        if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filePath.c_str())) {
            throw std::runtime_error(warn + err);
        }

        for (const auto& shape : shapes) {
            for (const auto& index : shape.mesh.indices) {
                Vertex vertex{};

                vertices.push_back(vertex);
                indices.push_back(indices.size());
                vertex.position = {attrib.vertices[3 * index.vertex_index + 0], attrib.vertices[3 * index.vertex_index + 1],
                                   attrib.vertices[3 * index.vertex_index + 2]};

                // vertex.texCoord = {attrib.texcoords[2 * index.texcoord_index + 0], attrib.texcoords[2 * index.texcoord_index + 1]};

                vertex.color = {1.0f, 1.0f, 1.0f};
            }
        }

        this->init(vertices, indices);
    }

    Model::~Model() {}

    void Model::init(const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices) {
        this->vertexCount = static_cast<uint32_t>(vertices.size());
        this->indexCount = static_cast<uint32_t>(indices.size());

        this->createVertexBuffer(vertices);

        if (indices.size() > 0) {
            this->createIndexBuffer(indices);
        }
    }

    void Model::createVertexBuffer(const std::vector<Vertex>& vertices) {
        BufferDirector bufferDirector{};

        VkDeviceSize vertexBufferSize = sizeof(vertices[0]) * vertices.size();
        std::unique_ptr<Buffer> upStagingBuffer = bufferDirector.makeStagingBuffer(this->pLogicalDevice, vertexBufferSize);
        std::unique_ptr<Memory> upStagingBufferMemory =
            std::make_unique<Memory>(this->pLogicalDevice, upStagingBuffer.get(), VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
        upStagingBuffer->bindMemory(upStagingBufferMemory.get());
        void** ppStagingBufferVertexData = upStagingBuffer->getMemory()->map();
        memcpy(*ppStagingBufferVertexData, vertices.data(), upStagingBuffer->getSize());
        upStagingBuffer->getMemory()->unmap();

        this->upVertexBuffer = bufferDirector.makeVertexTransferDestinationBuffer(this->pLogicalDevice, sizeof(vertices[0]) * vertices.size());
        this->upVertexMemory = std::make_unique<Memory>(this->pLogicalDevice, upVertexBuffer.get(), VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        this->upVertexBuffer->bindMemory(this->upVertexMemory.get());

        std::vector<VkBufferCopy> regions = {{.srcOffset = 0, .dstOffset = 0, .size = vertexBufferSize}};

        CommandRecording* pCommandRecording = this->pLogicalDevice->beginSingleTimeCommandRecording(this->pLogicalDevice->getGraphicsQueue());
        upStagingBuffer->copyTo(pCommandRecording->pPrimaryCommandBuffers[0], this->upVertexBuffer.get(), regions);
        this->pLogicalDevice->endSingleTimeCommandRecording(pCommandRecording);
    }

    void Model::createIndexBuffer(const std::vector<uint16_t>& indices) {
        BufferDirector bufferDirector{};

        VkDeviceSize indexBufferSize = sizeof(indices[0]) * indices.size();
        std::unique_ptr<Buffer> upStagingBuffer = bufferDirector.makeStagingBuffer(this->pLogicalDevice, indexBufferSize);
        std::unique_ptr<Memory> upStagingBufferMemory =
            std::make_unique<Memory>(this->pLogicalDevice, upStagingBuffer.get(), VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
        upStagingBuffer->bindMemory(upStagingBufferMemory.get());
        void** ppStagingBufferVertexData = upStagingBuffer->getMemory()->map();
        memcpy(*ppStagingBufferVertexData, indices.data(), upStagingBuffer->getSize());
        upStagingBuffer->getMemory()->unmap();

        this->upIndexBuffer = bufferDirector.makeIndexTransferDestinationBuffer(this->pLogicalDevice, sizeof(indices[0]) * indices.size());
        this->upIndexMemory = std::make_unique<Memory>(this->pLogicalDevice, upIndexBuffer.get(), VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
        this->upIndexBuffer->bindMemory(this->upIndexMemory.get());

        std::vector<VkBufferCopy> regions = {{.srcOffset = 0, .dstOffset = 0, .size = indexBufferSize}};

        CommandRecording* pCommandRecording = this->pLogicalDevice->beginSingleTimeCommandRecording(this->pLogicalDevice->getGraphicsQueue());
        upStagingBuffer->copyTo(pCommandRecording->pPrimaryCommandBuffers[0], this->upIndexBuffer.get(), regions);
        this->pLogicalDevice->endSingleTimeCommandRecording(pCommandRecording);
    }

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